#ifndef POPULATION_H
#define POPULATION_H

#include "chromosome_class.h"

using namespace std;

class Population {
  public:
    Population();
    // Chromosome * getElite(void); /* Returns an array containing the top two vectors. */
    // Chromosome * getRandomPair(void); /* Returns an array containing two random vectors. */
    Hallele * matePair(Hallele *a, Hallele *b); /* Returns the offspring of a pair of chromosomes. */
    void printPopulation(void); /* Prints each vector of the current population. */
    void printFitness(void); /* Prints each vector's fitness value of the current population. */
    void initializePopulation(int popSize, int chromSize);
    void updateFitness(int index, double fitness); /* Updates the fitness of a solution indexed by 'index'. */

    void mateIndividuals(void);
    void introduceMutants(); /* Replaces 25% of the 'non-elit' halfh with mutant individuals. */
    Hallele * getSolutionAsArray(int solIndex);
    // bool initializeUpdateDemand(int ind, double demand);
    Chromosome getSingleChromosome(int index);

    void swap(Chromosome *a, Chromosome *b);
    int partition(Chromosome *array, int low, int high);
    void quickSort(Chromosome *array, int low, int high);
    void sortByFitness(void);
    // void evolve(); /* Some of the above functions should be private. The evolve method will use 'em to manipulate the vectors. */

  private:
    int size;
    Chromosome *population;
};

#endif
