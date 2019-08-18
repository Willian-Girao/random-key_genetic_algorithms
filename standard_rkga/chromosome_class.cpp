#include <iostream>
#include <array>
#include <stdlib.h>

#include "chromosome_class.h"

using namespace std;

Chromosome::Chromosome() {
  fitness = ((double) rand() / RAND_MAX);
}

// /* Private methods */

void Chromosome::setFitness(double fit) {
  fitness = fit;
}

void Chromosome::generateGenes(int chromosomeSize) {
  length = chromosomeSize;
  genes = new Hallele[length];

  for (int i = 0; i < chromosomeSize; i++) {    
    double key = ((double) rand() / RAND_MAX);

    while (key == 1.0) {
      key = ((double) rand() / RAND_MAX);
    }

    Hallele h;

    h.key = key;
    h.index = i;

    genes[i] = h;
  }
}

void Chromosome::updateGene(int i, double key) {
  genes[i].key = key;
}

// /* Public methods */


double Chromosome::getFitness(void) {
  return fitness;
}

double Chromosome::getGene(int index) {
  return genes[index].key;
}

void Chromosome::printGenes(void) {
  for (int i = 0; i < length; i++) {
    cout << genes[i].key << endl;
  }
}
