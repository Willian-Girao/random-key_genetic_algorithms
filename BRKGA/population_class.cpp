#include <iostream>
#include <array>
#include <stdlib.h>
#include <math.h>

#include "population_class.h"
#include "instance_class.h"

#include "neighborhood_structures.cpp"

using namespace std;

/* Public methods */

Population::Population() {
}

void Population::initializePopulation(int popSize, int chromSize) {
  size = popSize;
  population = new Chromosome[popSize];

  for (int i = 0; i < popSize; i++) {
    Chromosome chrom;
    chrom.generateGenes(chromSize);
    population[i] = chrom;
  }
}

void Population::swap(Chromosome *a, Chromosome *b) {
	Chromosome temp = *a;
	*a = *b;
	*b = temp;
}

int Population::partition(Chromosome *array, int low, int high) {
	double pivot = array[high].getFitness();
	int sml = (low - 1); // Smalest emelent's index.

	for (int i = low; i <= (high - 1); ++i)
	{
		if (array[i].getFitness() <= pivot)
		{			
			sml++;
			swap(&array[sml], &array[i]);
		}
	}

	swap(&array[sml + 1], &array[high]);
	return (sml + 1);
}

void Population::quickSort(Chromosome *array, int low, int high) {
	if (low < high)
	{
		//'pi' is 'partitioning index', array[p] is now at the right position.
		int pi = partition(array, low, high);

		quickSort(array, low, (pi - 1));
		quickSort(array, (pi + 1), high);
	}
}


void Population::sortByFitness(void) {
  quickSort(population, 0, size - 1);
}

Hallele * Population::matePair(Hallele *a, double aFitness, Hallele *b, double bFitness) {
  double prob;

  int crossoverPoint = rand() % (population[0].getLength() - 1); /* [0,length-2)]*/

  if (crossoverPoint == 0)
  {
  	crossoverPoint = 1;
  }

  Hallele *offspring = new Hallele[population[0].getLength()];

  //Initializing offspring
  offspring[0].index = 0;
  offspring[0].key = 0.0;
  for (int i = 1; i < population[0].getLength(); ++i)
  {
  	offspring[i].index = i;
  }
  offspring[population[0].getLength()-1].index = 0;

  double lowestKey = 2.0;
  int lowestKeySensor = 0;
  int lowestKeyIndex = 1;

  for (int i = 1; i < population[0].getLength(); i++) 
  {
  	//Crossover gives priority to the parent with the best fitness value
    if (aFitness <= bFitness) //Parent 'a' has better fitness - biasing coin toss towards 'a'
    {
    	prob = ((double) rand() / RAND_MAX);

    	if (prob <= 0.7) //Parent 'a' won coin toss
    	{
	    	offspring[i].key = a[i].key;
	    	if (offspring[i].key < lowestKey)
	    	{
	    		lowestKey = offspring[i].key;
	    		lowestKeySensor = offspring[i].index;
	    		lowestKeyIndex = i;
	    	}
	    } else { //Parent 'b' won coin toss
		    offspring[i].key = b[i].key;
		    if (offspring[i].key < lowestKey)
	    	{
	    		lowestKey = offspring[i].key;
	    		lowestKeySensor = offspring[i].index;
	    		lowestKeyIndex = i;
	    	}
	    }
    } else { //Parent 'b' has better fitness - biasing coin toss towards 'b'
    	prob = ((double) rand() / RAND_MAX);

    	if (prob <= 0.7) //Parent 'b' won coin toss
    	{
	    	offspring[i].key = b[i].key;
	    	if (offspring[i].key < lowestKey)
	    	{
	    		lowestKey = offspring[i].key;
	    		lowestKeySensor = offspring[i].index;
	    		lowestKeyIndex = i;
	    	}
	    } else { //Parent 'a' won coin toss
		    offspring[i].key = a[i].key;
		    if (offspring[i].key < lowestKey)
	    	{
	    		lowestKey = offspring[i].key;
	    		lowestKeySensor = offspring[i].index;
	    		lowestKeyIndex = i;
	    	}
	    }
    }
  }

  if (lowestKeySensor == 0)
  {
    int swapA = (rand() % (population[0].getLength() - 2)) + 2;
    while (swapA == lowestKeyIndex)
    {
      swapA = (rand() % (population[0].getLength() - 2)) + 2;
    }

    double tempI = offspring[swapA].index;

    offspring[swapA].index = lowestKeySensor;

    offspring[lowestKeyIndex].index = tempI;
  }

  return offspring;
}

void Population::printPopulation(void) {
  for (int i = 0; i < size; i++) {
    cout << "Vector " << i << " (" << population[i].getFitness() << ")" << endl;
    population[i].printGenes();
    cout << endl;
  }
}

Hallele * Population::getSolutionAsArray(int solIndex) {
	return population[solIndex].getChromosomeAsArray();
}

void Population::updateFitness(int index, double fitness) {
	if (population[index].getFitness() == 0.0)
	{
		population[index].setFitness(fitness);
	}
}

void Population::resetEvaluateFlag(int index) {
	population[index].resetEvaluateFlag();
}

void Population::setEvaluateFlag(int index) {
	population[index].setEvaluateFlag();
}

bool Population::shouldCalcFitness(int index) {
	return population[index].shouldCalcFitness();
}

void Population::updateSolutionHalleles(int index, Hallele *newHallele) {
	population[index].setResetGenes(newHallele);
}

void Population::introduceMutants(void) {
	int endIndex = floor((size / 4.0)); //End index when introducing mutants.
	int index = size - 1;

	//Reseting 25% of the population (introducing mutants).
	while(endIndex > 0)
	{
		// cout << "Solution " << index << " became a mutant.\n";
		population[index].resetChromosome();
		population[index].setFitness(0.0);
		population[index].setEvaluateFlag();

		index--;
		endIndex--;
	}
}

Chromosome Population::getSingleChromosome(int index) {
	return population[index];
}

void Population::mateIndividuals(void) {
	int numMutants = floor((size / 4.0));
	int x = size - ceil((size / 2.0)) - floor((size / 4.0));

	int indexStartRand = size - ceil((size / 2.0));
	int indexEndRand = size - 1;

	// cout << "numMutants: " << numMutants << endl;
	// cout << "q: " << (size - ceil((size / 2.0))) << endl;

	//Indexes of chromosomes to be overrided by mating result.
	for (int i = (size - numMutants - 1); i >= (size - ceil((size / 2.0))); --i)
	{
		// int parentAIndex = rand() % (size - indexStartRand) + indexStartRand;
		// int parentBIndex = rand() % (size - indexStartRand) + indexStartRand;
		int parentAIndex = rand() % (size / 2);
		int parentBIndex = rand() % (size / 2);

		while(parentBIndex == parentAIndex) {
			parentBIndex = rand() % (size / 2);
		}

		// cout << "Parent A: " << parentAIndex << endl;
		// cout << "Parent B: " << parentBIndex << endl;
		// cout << "Individual " << i << " became offspring\n";

		population[i].setResetGenes(matePair(population[parentAIndex].getChromosomeAsArray(), population[parentAIndex].getFitness(), population[parentBIndex].getChromosomeAsArray(), population[parentBIndex].getFitness()));
		population[i].setEvaluateFlag();
	}

	// int a;
	// cin >> a;
}

void Population::resetInvalidSolutions(void) {
	for (int i = 0; i < size; ++i)
	{
	    if (population[i].getFitness() < 0.0)
		{
			population[i].resetGenes();
		}
	}
}

/* Private methods */

void Population::localSearch(int index, double muleVelocity, Instance *inst) {
	SolutionStruct *solutionAux = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
	
	double inputSolFitness = population[index].getFitness();
	double newSolFitness = -1.0;
	double auxSolFitness = -1.0;
	
	int solLenghth = population[index].getLength();
	int Kmax = 3;
	int neighborhoodStructure = -1; /* Randomly selects what neighborhood structure to use */

	bool keepVnd = true;

	/* VND */
	while (keepVnd)
	{
		// neighborhoodStructure = rand() % 3;
		neighborhoodStructure = 0;
		auxSolFitness = newSolFitness;

		for (int i = 0; i < Kmax; ++i)
		{
			if (neighborhoodStructure == 0) 		/* N-Swap */
			{
				nSwap(solutionAux, solLenghth);
			} else if (neighborhoodStructure == 1) {
				nSwap21(solutionAux, solLenghth);
			} else {
				nShift(solutionAux, solLenghth);
			}

			newSolFitness = inst->evaluateLocalSearchSolution(solutionAux, muleVelocity, false);

			if (newSolFitness >= inputSolFitness || newSolFitness == 0)
			{
				solutionAux = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
				// neighborhoodStructure = rand() % 3;
				neighborhoodStructure += 1;
			} 
		}

		if (newSolFitness >= auxSolFitness)
		{
			break;
		}
	}

	// cout << "\na";
	if (newSolFitness < inputSolFitness && newSolFitness != 0)
	{
		// cout << "\nb";
		// cout << "\n\n";
		// population[index].printGenes();
		// cout << "\n\n";
		for (int i = 0; i < solLenghth; ++i)
		{
			population[index].updateKeysIndex(solutionAux[i].key, solutionAux[i].node);
		}
		// inst->evaluateLocalSearchSolution(solutionAux, muleVelocity, true);
		population[index].setFitness(newSolFitness);
		// cout << "inputSolFitness: " << inputSolFitness << " , newSolFitness: " << newSolFitness << endl;
		// for (int i = 0; i < solLenghth; ++i)
	 //    {
	 //      cout << solutionAux[i].node << " ";
	 //    }
	 //    cout << "\n";

		// inst->evaluateLocalSearchSolution(solutionAux, muleVelocity, true);
		// population[index].printGenes();
		// cout << "\n\n";

		// int a = 0;
		// cin >> a;
	}
}