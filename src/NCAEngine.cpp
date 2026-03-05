#include "NCAEngine.h"
#include <cmath>
#include <cstdint>
#include <iostream>
#include <random>

NCAEngine::NCAEngine() : grid_sprite(grid_texture) {
  grid.resize(GRID_WIDTH * GRID_HEIGHT);
  next_grid.resize(GRID_WIDTH * GRID_HEIGHT);
  grid_texture.resize({(unsigned int)GRID_WIDTH, (unsigned int)GRID_HEIGHT});

  seed_center();
}

void NCAEngine::seed_center() {
  std::fill(grid.begin(), grid.end(), Cell{});
  std::fill(next_grid.begin(), next_grid.end(), Cell{});

  int center = GRID_WIDTH / 2 + (GRID_HEIGHT / 2) * GRID_WIDTH;
  grid[center].channels[3] = 1.0f; // Life
  grid[center].channels[0] = 1.0f; // Red seed
  grid[center].channels[4] = 1.0f;
}

void NCAEngine::reset_to_random() {
  active_genome = Genome();
  seed_center();
}

Cell &NCAEngine::get_cell(int x, int y, std::vector<Cell> &target_grid) {
  if (x < 0)
    x += GRID_WIDTH;
  else if (x >= GRID_WIDTH)
    x -= GRID_WIDTH;

  if (y < 0)
    y += GRID_HEIGHT;
  else if (y >= GRID_HEIGHT)
    y -= GRID_HEIGHT;

  return target_grid[x + y * GRID_WIDTH];
}

void NCAEngine::update() {
  TinyML::Matrix input_mat(1, INPUT_SIZE);
  TinyML::Matrix hidden_mat(1, HIDDEN_NEURONS);
  TinyML::Matrix output_mat(1, CHANNELS);

  for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
      // 1. Alive Mask: Check if there's any living neighbor in a 3x3 area
      bool has_living_neighbor = false;
      for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
          if (get_cell(x + dx, y + dy, grid).channels[3] > 0.1f) {
            has_living_neighbor = true;
            break;
          }
        }
        if (has_living_neighbor)
          break;
      }

      // If no living neighbors, the cell is strictly dead and zeroed out
      if (!has_living_neighbor) {
        get_cell(x, y, next_grid) = Cell{};
        continue;
      }

      // 2. Stochastic update mask
      if (rand() % 2 == 0) {
        next_grid[x + y * GRID_WIDTH] = grid[x + y * GRID_WIDTH];
        continue;
      }

      Cell &c = get_cell(x, y, grid);
      Cell tl = get_cell(x - 1, y - 1, grid);
      Cell t = get_cell(x, y - 1, grid);
      Cell tr = get_cell(x + 1, y - 1, grid);
      Cell l = get_cell(x - 1, y, grid);
      Cell r = get_cell(x + 1, y, grid);
      Cell bl = get_cell(x - 1, y + 1, grid);
      Cell b = get_cell(x, y + 1, grid);
      Cell br = get_cell(x + 1, y + 1, grid);
      for (int ch = 0; ch < CHANNELS; ch++) {

        float grad_x =
            (tr.channels[ch] + 2.0f * r.channels[ch] + br.channels[ch]) -
            (tl.channels[ch] + 2.0f * l.channels[ch] + bl.channels[ch]);
        float grad_y =
            (bl.channels[ch] + 2.0f * b.channels[ch] + br.channels[ch]) -
            (tl.channels[ch] + 2.0f * t.channels[ch] + tr.channels[ch]);
        input_mat.data[ch] = c.channels[ch];
        input_mat.data[ch + 16] = grad_x;
        input_mat.data[ch + 32] = grad_y;
      }

      active_genome.layer1.forward(input_mat, hidden_mat);
      TinyML::relu(hidden_mat);

      active_genome.layer2.forward(hidden_mat, output_mat);

      Cell &next_c = get_cell(x, y, next_grid);
      for (int i = 0; i < CHANNELS; i++) {
        float delta = output_mat.data[i];
        float val = c.channels[i] + delta * 0.1f;
        next_c.channels[i] = std::max(0.0f, std::min(1.0f, val));
      }
    }
  }
  grid = next_grid;
}

void NCAEngine::draw(sf::RenderWindow &window) {
  std::uint8_t *pixels = new std::uint8_t[GRID_WIDTH * GRID_HEIGHT * 4];
  for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
    pixels[i * 4 + 0] =
        (std::uint8_t)(std::clamp(grid[i].channels[0], 0.0f, 1.0f) * 255);
    pixels[i * 4 + 1] =
        (std::uint8_t)(std::clamp(grid[i].channels[1], 0.0f, 1.0f) * 255);
    pixels[i * 4 + 2] =
        (std::uint8_t)(std::clamp(grid[i].channels[2], 0.0f, 1.0f) * 255);
    pixels[i * 4 + 3] =
        (std::uint8_t)(std::clamp(grid[i].channels[3], 0.0f, 1.0f) * 255);
  }

  grid_texture.update(pixels);
  delete[] pixels;
  grid_sprite.setTexture(grid_texture, true);
  grid_sprite.setScale({(float)CELL_SIZE, (float)CELL_SIZE});
  window.draw(grid_sprite);
}

float NCAEngine::evaluate_homeostasis(int steps) {
  seed_center();

  // Phase 1: Growth
  for (int i = 0; i < steps; i++) {
    update(); // simulate evolution without rendering
  }

  // Phase 2: Homeostasis - measure stability by sampling
  float total_error = 0.0f;
  float ideal = 83.0f;
  int sample_steps = 20;

  for (int step = 0; step < sample_steps; step++) {
    int living = 0;
    for (int i = 0; i < GRID_WIDTH * GRID_HEIGHT; i++) {
      if (grid[i].channels[3] > 0.1f)
        living++;
    }
    total_error += std::abs(living - ideal);
    update();
  }

  float avg_error = total_error / (float)sample_steps;
  return 1.0f - avg_error / ideal;
}
