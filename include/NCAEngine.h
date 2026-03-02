#pragma once

#include<SFML/Graphics.hpp>
#include<vector>
#include "config.h"
#include"TinyML.h"
#include "Genome.h"

struct Cell{
    float channels[CHANNELS]={0.0f};
};

class NCAEngine{
private:
    std::vector<Cell> grid;
    std::vector<Cell> next_grid;//to enable simultaneous updates

    sf::Image grid_image;
    sf::Texture grid_texture;
    sf::Sprite grid_sprite;

    Cells& get_cell(int x, int y, std::vector<Cell>& grid);
public:
    Genome active_genome;
    NCAEngine();
    void update();
    void draw(sf::RenderWindow& window);
    void reset_to_random();
    void seed_center();

};

