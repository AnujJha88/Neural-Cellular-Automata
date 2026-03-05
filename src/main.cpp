#include "GenomeOps.h"
#include "NCAEngine.h"
#include "PopulationManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main() {
  // SFML 3 uses sf::Vector2u instead of raw ints for VideoMode
  sf::RenderWindow window(
      sf::VideoMode({(unsigned int)(GRID_WIDTH * CELL_SIZE),
                     (unsigned int)(GRID_HEIGHT * CELL_SIZE)}),
      "NCA Phase 2:Training");
  window.setFramerateLimit(60);

  auto desktop = sf::VideoMode::getDesktopMode();
  window.setPosition({(int)(desktop.size.x / 2 - window.getSize().x / 2),
                      (int)(desktop.size.y / 2 - window.getSize().y / 2)});

  NCAEngine engine;
  PopulationManager pop(100);

  engine.active_genome = pop.get_best_genome();

  std::cout << "Controls:\n [R] - Randomize Genome\n [M] - Mutate Current\n "
               "[Space] - Reset Grid"
            << std::endl;

  while (window.isOpen()) {

    // SFML 3 uses std::optional for the event loop
    while (const std::optional<sf::Event> event = window.pollEvent()) {

      // Check for window close
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      // Check for key presses using the new getIf<>
      if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {

        // Keyboard enums changed to sf::Keyboard::Key::[Letter]
        if (keyPressed->code == sf::Keyboard::Key::R) {
          engine.reset_to_random();
          std::cout << "Genome randomized!" << std::endl;
        }
        if (keyPressed->code == sf::Keyboard::Key::M) {
          GenomeOps::mutate(engine.active_genome, 0.1f, 0.1f);
          std::cout << "Genome mutated!" << std::endl;
        }
        if (keyPressed->code == sf::Keyboard::Key::Space) {
          engine.seed_center();
          std::cout << "Grid Reset!" << std::endl;
        }
        if (keyPressed->code == sf::Keyboard::Key::T) {
          std::cout << "Evolving population" << std::flush;
          pop.evolve_one_gen();
          engine.active_genome = pop.get_best_genome();
          engine.seed_center();

          std::cout << "Done!\n";
        }
      }
    }

    engine.update();
    window.clear();
    engine.draw(window);
    window.display();
  }
  return 0;
}
