#ifndef POPULATION_H
#define POPULATION_H

#include "chromosome_class.h"

using namespace std;

class Population {
  public:
    Population();

    /* Getters */
    Hallele * matePair(Hallele *a, Hallele *b); /* Returns the offspring of a pair of chromosomes. */
    Hallele * getSolutionAsArray(int solIndex); /* Returns the chromosome sequence of alleles - RKGA encoding */
    Chromosome getSingleChromosome(int index); /* Returns the object instance of one of the chromosomes within the population. */

    /* Setters */
    void initializePopulation(int popSize, int chromSize); /* Sets population size and solution array length. */
    void updateFitness(int index, double fitness); /* Updates the fitness of a solution indexed by 'index'. */
    void mateIndividuals(void); /* Produces offsprings of solutions - 'popSize' even 25% of population | 'popSize' odd 20% of population */
    void introduceMutants(); /* Replaces 25% of the 'non-elit' halfh with mutant individuals. */
    void sortByFitness(void); /* Sorts the population in descending ascending order based on the fitness values. */

    /* Utils */
    void printPopulation(void); /* Prints each vector of the current population. */
    void printFitness(void); /* Prints each vector's fitness value of the current population. */

    /* Utilities */
    void swap(Chromosome *a, Chromosome *b); /* Utilized to swap two soltuions within the solution array. */
    int partition(Chromosome *array, int low, int high); /* Utilized within the method performing quicksort. */
    void quickSort(Chromosome *array, int low, int high); /* Quicksort utilized to sort population by fitness. */

  private:
    int size; /* Number of individuals within the population. */
    Chromosome *population; /* Population as array of chromosomes. */
};

#endif
