#ifndef POPULATION_H
#define POPULATION_H

#include "chromosome_class.h"

using namespace std;

class Population {
  public:
    Population();
    Chromosome * getElite(void); /* Returns an array containing the top two vectors. */
    Chromosome * getRandomPair(void); /* Returns an array containing two random vectors. */
    Chromosome matePair(Chromosome a, Chromosome b); /* Returns the offspring of a pair of chromosomes. */
    void printPopulation(void); /* Prints each vector of the current population. */
    void printFitness(void); /* Prints each vector's fitness value of the current population. */
    // void evolve(); /* Some of the above functions should be private. The evolve method will use 'em to manipulate the vectors. */

  private:
    array<Chromosome,6> population;
};

#endif
