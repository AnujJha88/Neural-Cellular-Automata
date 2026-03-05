#include "PopulationManager.h"
#include <future>
#include <iostream>

PopulationManager::PopulationManager(int size) {
  this->size = size;
  for (int i = 0; i < size; ++i) {
    population.push_back({Genome(), 0.0f});
  }
}

void PopulationManager::evolve_one_gen() {
  std::vector<std::future<void>> futures;

  for (auto &ind : population) {
    // Spawn a background thread for each genome
    futures.push_back(std::async(std::launch::async, [&ind]() {
      NCAEngine eval_engine;
      eval_engine.active_genome = ind.dna;
      ind.fitness = eval_engine.evaluate_homeostasis(100);
    }));
  }

  for (auto &f : futures) {
    f.get();
  }

  std::sort(population.begin(), population.end(),
            [](const Individual &a, const Individual &b) {
              return a.fitness > b.fitness;
            });

  std::cout << "Gen " << generation << " | Top Score: " << population[0].fitness
            << std::endl;

  std::vector<Individual> next_gen;

  for (int i = 0; i < 5; ++i) {
    next_gen.push_back(population[i]);
  }

  while (next_gen.size() < (size_t)size) {
    int p1 = rand() % (size / 2);
    int p2 = rand() % (size / 2);

    Genome child = GenomeOps::crossover(population[p1].dna, population[p2].dna);
    GenomeOps::mutate(child, 0.1f, 0.05f);

    next_gen.push_back({child, 0.0f});
  }

  population = next_gen;
  generation++;
}

Genome PopulationManager::get_best_genome() { return population[0].dna; }