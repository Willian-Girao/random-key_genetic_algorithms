#include <iostream>
#include <array>
#include <stdlib.h>

#include "population_class.h"

using namespace std;

/* Public methods */

Population::Population() {
  for (size_t i = 0; i < population.size(); i++) {
    Chromosome chromosome;
    population[i] = chromosome;
  }
}

Chromosome * Population::getElite(void) {
  static Chromosome elite[2];

  elite[0] = population[0];
  elite[1] = population[1];

  for (size_t i = 1; i < population.size(); i++) {
    if (population[i].getFitness() < elite[0].getFitness()) {
      elite[1] = elite[0];
      elite[0] = population[i];
    } else if (population[i].getFitness() < elite[1].getFitness()) {
      elite[1] = population[i];
    }
  }

  cout << "Vector 0: " << elite[0].getFitness() << endl;
  cout << "Vector 1: " << elite[1].getFitness() << endl;

  return elite;
}

void Population::printPopulation(void) {
  for (size_t i = 0; i < population.size(); i++) {
    cout << "Vector " << i << endl;
    population[i].printGenes();
    cout << endl;
  }
}

void Population::printFitness(void) {
  for (size_t i = 0; i < population.size(); i++) {
    cout << "Vector " << i << ": " << population[i].getFitness() << endl;
  }
  cout << endl;
}

/* Private methods */
