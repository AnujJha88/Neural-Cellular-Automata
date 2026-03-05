#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "NCAEngine.h"
#include "GenomeOps.h"
#include <iostream>

int main() {
    // SFML 3 uses sf::Vector2u instead of raw ints for VideoMode
    sf::RenderWindow window(sf::VideoMode({(unsigned int)(GRID_WIDTH * CELL_SIZE), (unsigned int)(GRID_HEIGHT * CELL_SIZE)}), "NCA Phase 1.5: SFML 3.0");
    window.setFramerateLimit(60);

    NCAEngine engine;

    std::cout << "Controls:\n [R] - Randomize Genome\n [M] - Mutate Current\n [Space] - Reset Grid" << std::endl;

    while (window.isOpen()) {

        // SFML 3 uses std::optional for the event loop
        while (const std::optional<sf::Event> event = window.pollEvent()) {

            // Check for window close
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Check for key presses using the new getIf<>
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

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
            }
        }

        engine.update();
        window.clear();
        engine.draw(window);
        window.display();
    }
    return 0;
}
