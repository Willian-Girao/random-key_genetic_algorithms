#include <iostream>
#include <array>
#include <stdlib.h>

#include "chromosome_class.h"

using namespace std;

/* Private methods */

void Chromosome::setFitness(double fit) {
  fitness = fit;
}

void Chromosome::generateGenes(void) {
  for (size_t i = 0; i < genes.size(); i++) {
    double key = ((double) rand() / RAND_MAX);
    while (key == 1.0) {
      key = ((double) rand() / RAND_MAX);
    }
    genes[i] = key;
  }
}

void Chromosome::updateGene(int i, double key) {
  genes[i] = key;
}

/* Public methods */

Chromosome::Chromosome() {
  // fitness = 0.0;
  fitness = ((double) rand() / RAND_MAX);
  generateGenes();
}

double Chromosome::getFitness(void) {
  return fitness;
}

void Chromosome::calculateFitness(void) {
  double updatedFitness = 0.0;
  // get chromosome genes here and evaluate the objective funtion (that should be passed as argument)
  setFitness(updatedFitness);
}

double Chromosome::getGene(int index) {
  return genes[index];
}

void Chromosome::printGenes(void) {
  for (size_t i = 0; i < genes.size(); i++) {
    cout << genes[i] << endl;
  }
}
