#include "NCAEngine.h"
#include <cmath>
#include <iostream>
#include <random>

NCAEngine::NCAEngine() {
    grid.resize(GRID_WIDTH * GRID_HEIGHT);
    next_grid.resize(GRID_WIDTH * GRID_HEIGHT);
    grid_image.create(GRID_WIDTH, GRID_HEIGHT, sf::Color::Black);

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

Cell& NCAEngine::get_cell(int x, int y, std::vector<Cell&>target_grid){
    x=(x+GRID_WIDTH)%GRID_WIDTH;
    y=(y+GRID_HEIGHT)%GRID_HEIGHT;
    return target_grid[x+y*GRID_WIDTH];
}

void NCAEngine::update(){
    TinyML:Matrix input_mat(1,INPUT_SIZE);
    TinyML::Matrix hidden_mat(1,HIDDEN_NEURONS);
    TinyML::Matrix output_mat(1,CHANNELS);

    for(int y=0;y<GRID_HEIGHT;y++){
        for(int x=0;x<GRID_WIDTH;x++){
            if(rand()%2==0){
                next_grid[x+y*GRID_WIDTH]=grid[x+y*GRID_WIDTH];
                continue;
            }

            Cell& c=get_cell(x,y,grid);
            for(int ch = 0; ch < CHANNELS; ch++) {
                float tl = get_cell(x-1, y-1, grid).channels[ch];
                float t  = get_cell(x,   y-1, grid).channels[ch];
                float tr = get_cell(x+1, y-1, grid).channels[ch];
                float l  = get_cell(x-1, y,   grid).channels[ch];
                float r  = get_cell(x+1, y,   grid).channels[ch];
                float bl = get_cell(x-1, y+1, grid).channels[ch];
                float b  = get_cell(x,   y+1, grid).channels[ch];
                float br = get_cell(x+1, y+1, grid).channels[ch];

                float grad_x = (tr + 2.0f * r + br) - (tl + 2.0f * l + bl);
                float grad_y = (bl + 2.0f * b + br) - (tl + 2.0f * t + tr);

                input_mat.data[ch]      = c.channels[ch];
                input_mat.data[ch + 16] = grad_x;
                input_mat.data[ch + 32] = grad_y;
            }

            active_genome.layer1.forward(input_mat,hidden_mat);
            TinyML::relu(hidden_mat);

            active_genome.layer2.forward(hidden_mat,output_mat);


            Cell& next_c=get_cell(x,y,next_grid);
            for(int i=0;i<CHANNELS;i++){
                float delta=output_mat.data[i];
                float val=c.channels[i]+delta*0.1f;
                next_c.channels[i] = std::max(0.0f, std::min(1.0f, val));
            }
        }
    }
}
