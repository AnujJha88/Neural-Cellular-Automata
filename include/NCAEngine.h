#pragma once

#include "Genome.h"
#include "TinyML.h"
#include "config.h"
#include <SFML/Graphics.hpp>
#include <vector>

struct Cell {
  float channels[CHANNELS] = {0.0f};
};

class NCAEngine {
private:
  std::vector<Cell> grid;
  std::vector<Cell> next_grid; // to enable simultaneous updates

  sf::Texture grid_texture;
  sf::Sprite grid_sprite;

  Cell &get_cell(int x, int y, std::vector<Cell> &grid);

public:
  Genome active_genome;
  NCAEngine();
  void update();
  void draw(sf::RenderWindow &window);
  void reset_to_random();
  void seed_center();
  float evaluate_homeostasis(int steps);
};
