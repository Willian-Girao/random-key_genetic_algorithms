#ifndef POPULATION_H
#define POPULATION_H

#include "chromosome_class.h"
#include "instance_class.h"

using namespace std;

class Population {
  public:
    Population();

    /* Getters */
    Hallele * matePair(Hallele *a, double aFitness, Hallele *b, double bFitness); /* Returns the offspring of a pair of chromosomes. */
    Hallele * matePair004(Hallele *a, double aFitness, Hallele *b, double bFitness, Instance *inst, double muleVelocity); /* Returns the offspring of a pair of chromosomes. */
    SolutionStruct * matePairBRKGA02(Hallele *a, Hallele *b, Instance *inst, double muleVelocity); /* Returns the offspring of a pair of chromosomes using SCX. */
    SolutionStruct * modularCrossover(Chromosome a, Chromosome b, Instance *inst, double muleVelocity); /* Returns the offspring of a pair of chromosomes using SCX. */
    Hallele * getSolutionAsArray(int solIndex); /* Returns the chromosome sequence of alleles - RKGA encoding */
    Chromosome getSingleChromosome(int index); /* Returns the object instance of one of the chromosomes within the population. */

    /* Setters */
    void initializePopulation(int popSize, int chromSize); /* Sets population size and solution array length. */
    void updateFitness(int index, double fitness); /* Updates the fitness of a solution indexed by 'index'. */
    void mateIndividuals(Instance *inst, double muleVelocity); /* Produces offsprings of solutions - 'popSize' even 25% of population | 'popSize' odd 20% of population */
    void mateBRKGA02(Instance *inst, double muleVelocity); /* Produces offsprings of solutions - 'popSize' even 25% of population | 'popSize' odd 20% of population */
    void mateModularCrossover(Instance *inst, double muleVelocity); /* Produces offsprings of solutions - 'popSize' even 25% of population | 'popSize' odd 20% of population */
    void introduceMutants(void); /* Replaces 25% of the 'non-elit' halfh with mutant individuals. */
    void mutationBRKGA01(double mutationChoiceProb, double mutationBRKGA01Prob); /* Replaces 25% of the 'non-elit' halfh with mutant individuals. */
    void sortByFitness(void); /* Sorts the population in descending ascending order based on the fitness values. */
    void resetInvalidSolutions(void);
    void updateSolutionHalleles(int index, Hallele *newHallele);
    void resetEvaluateFlag(int index); /* Resets 'evaluate' back to true */
    void setEvaluateFlag(int index); /* Resets 'evaluate' back to true */

    bool shouldCalcFitness(int index);

    void insertNewGeneAt(SolutionStruct *sol, int indexEdit, int indexAux);
    int findeNextSensorIndexFromSensor(SolutionStruct *sol, int sensor, int size);

    // void localSearch(int index, double muleVelocity, Instance *inst); /* Upplies a loceal search to the chromosome 'index' */

    /* Utils */
    void printPopulation(void); /* Prints each vector of the current population. */
    void printFitness(void); /* Prints each vector's fitness value of the current population. */

    /* Utilities */
    void swap(Chromosome *a, Chromosome *b); /* Utilized to swap two soltuions within the solution array. */
    int partition(Chromosome *array, int low, int high); /* Utilized within the method performing quicksort. */
    void quickSort(Chromosome *array, int low, int high); /* Quicksort utilized to sort population by fitness. */

  private:
    int size; /* Number of individuals within the population. */
    // double peProb; /* Biased probability value towards elite solutions during crossover */
    Chromosome *population; /* Population as array of chromosomes. */
};

#endif
