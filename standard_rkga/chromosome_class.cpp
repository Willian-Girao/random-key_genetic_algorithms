#include <iostream>
#include <array>
#include <stdlib.h>

#include "chromosome_class.h"

using namespace std;

Chromosome::Chromosome() {
  fitness = 0.0;
}

// /* Private methods */

void Chromosome::setFitness(double fit) {
  fitness = fit;
}

/* Whipe cleans a chromosome - reset */
void Chromosome::resetChromosome(void) {
  for (int i = 1; i < length - 1; ++i)
  {
    double key = ((double) rand() / RAND_MAX);

    while (key == 1.0) {
      key = ((double) rand() / RAND_MAX);
    }

    genes[i].key = key;
    genes[i].index = i;
  }
}

void Chromosome::generateGenes(int chromosomeSize) {
  length = chromosomeSize + 1;
  genes = new Hallele[length];

  for (int i = 0; i < chromosomeSize; i++) {    
    double key = ((double) rand() / RAND_MAX);

    while (key == 1.0) {
      key = ((double) rand() / RAND_MAX);
    }

    Hallele h;

    h.key = key;
    h.index = i;
    // h.demand = 0.0;

    genes[i] = h;
  }

  Hallele bs; // Base Station.

  // The random key of the last index in the array is set to 1.0 as to always be 
  //at the end of the array during sorting from 1 to size.
  bs.key = 1.0;
  bs.index = 0;
  // bs.demand = 0.0;

  genes[chromosomeSize] = bs;
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
    cout << genes[i].key << " (" << genes[i].index << ")" << endl;
  }
}

Hallele * Chromosome::getChromosomeAsArray(void) {
  return genes;
}

// bool Chromosome::updateDemand(int ind, double demand) {
//   bool updated = false;

//   for (int i = 0; i < length; ++i)
//   {
//     if (genes[i].index == ind)
//     {
//       genes[i].demand = demand;
//       updated = true;
//     }
//   }

//   return updated;
// }
