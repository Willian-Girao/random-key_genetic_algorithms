#ifndef POPULATION_H
#define POPULATION_H

#include "chromosome_class.h"

using namespace std;

class Population {
  public:
    Population();
    Chromosome * getElite(void); /* Returns an array containing the top two vectors. */
    void printPopulation(void); /* Prints each vector of the current population. */
    void printFitness(void); /* Prints each vector's fitness value of the current population. */

  private:
    array<Chromosome,6> population;
};

#endif
