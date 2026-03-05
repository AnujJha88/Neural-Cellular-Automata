#pragma once
#include "Genome.h"
#include "GenomeOps.h"
#include "NCAEngine.h"
#include <algorithm>
#include <vector>

struct Individual {
  Genome dna;
  float fitness = 0.0f;
};

class PopulationManager {
public:
  std::vector<Individual> population;
  int generation = 0;
  int size;

  PopulationManager(int size);
  void evolve_one_gen();
  Genome get_best_genome();
};