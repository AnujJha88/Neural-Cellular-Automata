#pragma once
#include "Genome.h"
#include "TinyML.h"

namespace GenomeOps{
    void mutate(Genome& g,float rate, float strength);

    Genome crossover(const Genome& parentA, const Genome& parentB);

}
