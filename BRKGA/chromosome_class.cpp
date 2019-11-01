#include <iostream>
#include <array>
#include <stdlib.h>

#include "chromosome_class.h"

using namespace std;

// /* Public methods */

Chromosome::Chromosome() {
  fitness = 0.0;
}

int Chromosome::getLength(void) {
  return length;
}

void Chromosome::setResetGenes(Hallele * newGenes) {
  genes = newGenes;
  fitness = 0.0;
}

void Chromosome::setFitness(double fit) {
  fitness = fit;
}

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

  double key = ((double) rand() / RAND_MAX);

  while (key == 1.0) {
    key = ((double) rand() / RAND_MAX);
  }

  genes[length - 1].key = key;
  genes[length - 1].index = 0;

  // for (int i = 0; i < length; ++i)
  // {
  //   cout << genes[i].index << " ";
  // }
  // cout << endl;
}

void Chromosome::generateGenes(int chromosomeSize) {
  length = chromosomeSize + 1;
  genes = new Hallele[length];

  for (int i = 1; i < chromosomeSize; i++) {    
    double key = ((double) rand() / RAND_MAX);

    while (key == 1.0) {
      key = ((double) rand() / RAND_MAX);
    }

    Hallele h;

    h.key = key;
    h.index = i;

    genes[i] = h;
  }

  Hallele bs; // Base Station.

  double key = ((double) rand() / RAND_MAX);

  while (key == 1.0) {
    key = ((double) rand() / RAND_MAX);
  }

  bs.key = key;
  bs.index = 0;

  genes[chromosomeSize] = bs;

  Hallele h;
  h.key = 0.0;
  h.index = 0;

  genes[0] = h;
}

bool Chromosome::canInsertGene(Hallele * h, int gene) {
  bool allowedToInsert = true;

  for (int i = 1; i < length; ++i)
  {
    if (h[i].index == gene)
    {
      allowedToInsert = false;
    }
  }

  return allowedToInsert;
}

void Chromosome::removeGeneAt(Hallele * h, int gene) {
  for (int i = 1; i < length; ++i)
  {
    if (h[i].index == gene)
    {
      h[i].index = -1;
    }
  }
}

void Chromosome::resetEvaluateFlag(void) {
  mustEvaluate = false;
}

void Chromosome::setEvaluateFlag(void) {
  mustEvaluate = true;
}

bool Chromosome::shouldCalcFitness(void) {
  return mustEvaluate;
}

void Chromosome::complementMissingGene(Hallele * offspring, Hallele * aux, int position) {
  // cout << "offspring: ";
  // for (int i = 0; i < length; ++i)
  // {
  //   cout << offspring[i].index << " ";
  // }
  // cout << endl;
  // cout << "aux: ";
  // for (int i = 0; i < length; ++i)
  // {
  //   cout << aux[i].index << " ";
  // }
  // cout << endl;
  for (int i = 1; i < length; ++i)
  {
    if (aux[i].index != -1 && canInsertGene(offspring, aux[i].index))
    {
      offspring[position].index = aux[i].index;
      aux[i].index = -1;
      break;
    }
  }
  // cout << "aux after: ";
  // for (int i = 0; i < length; ++i)
  // {
  //   cout << aux[i].index << " ";
  // }
  // cout << endl << endl;
}

double Chromosome::getFitness(void) {
  return fitness;
}

double Chromosome::getGene(int index) {
  return genes[index].key;
}

int Chromosome::getIndex(int index) {
  return genes[index].index;
}

void Chromosome::printGenes(void) {
  for (int i = 0; i < length; i++) {
    cout << genes[i].key << " (" << genes[i].index << ")" << endl;
  }
}

Hallele * Chromosome::getChromosomeAsArray(void) {
  return genes;
}

// /* Private methods */

void Chromosome::updateGene(int i, double key) {
  genes[i].key = key;
}

void Chromosome::resetGenes() {
  for (int i = 1; i < (length - 1); i++) {    
    double key = ((double) rand() / RAND_MAX);

    while (key == 1.0) {
      key = ((double) rand() / RAND_MAX);
    }

    genes[i].key = key;
    genes[i].index = i;
  }

  double key = ((double) rand() / RAND_MAX);

  while (key == 1.0) {
    key = ((double) rand() / RAND_MAX);
  }

  genes[length-1].key = key;
  genes[length-1].index = 0;
}