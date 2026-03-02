#pragma once
#include "TinyML.h"
#include "config.h"

struct Genome{
    TinyML::Linear layer1;
    TinyML::Linear layer2;

    Genome(){
        layer1=TinyML::Linear(INPUT_SIZE,HIDDEN_NEURONS);
        layer2=TinyML::Linear(HIDDEN_NEURONS,CHANNELS);
    }
};
