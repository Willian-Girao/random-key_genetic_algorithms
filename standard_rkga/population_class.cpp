#include <iostream>
#include <array>
#include <stdlib.h>
#include <math.h>

#include "population_class.h"

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

Hallele * Population::matePair(Hallele *a, Hallele *b) {
  double prob;
  Hallele *offspring = new Hallele[population[0].getLength()];

  offspring[0].key = 0.0;
  offspring[0].index = 0;

  offspring[population[0].getLength()-1].key = 1.0;
  offspring[population[0].getLength()-1].index = 0;

  int countHelper = 0;
  for (int i = 1; i < (population[0].getLength() - 1); i++) {
    prob = ((double) rand() / RAND_MAX); /* TODO - this probability should be proportional to the vectors fitness value */
    double present = false;
    if (prob >= 0.5) {
      offspring[i].key = a[i].key;      
      for (int j = 1; j < countHelper+1; ++j)
	  {
		if (offspring[j].index == a[i].index)
      	{
      		present = true;
      	}
	  }

      if (!present)
      {
      	offspring[i].index = a[i].index;
      } else {
      	present = false;      	

      	for (int j = 1; j < countHelper+1; ++j)
		{
			if (offspring[j].index == b[i].index)
	      	{
	      		present = true;
	      	}
		}

		if (!present)
		{
			offspring[i].index = b[i].index;
		} else {
			//See what can came here (what number).
			int outHelp = 1;
			for (int x = 1; x < countHelper+1; ++x)
			{
			  	if (offspring[x].index == outHelp)
			  	{
			  		outHelp = offspring[x].index + 1;
			  	}
			}
			offspring[i].index = outHelp;
		}	
      }
    } else {
	    offspring[i].key = b[i].key;
	    for (int j = 1; j < countHelper+1; ++j)
    	{
    		if (offspring[j].index == b[i].index)
	      	{
	      		present = true;
	      	}
    	}

		if (!present)
	    {
      		offspring[i].index = b[i].index;
      	} else {
      		present = false;      	

	      	for (int j = 1; j < countHelper+1; ++j)
			{
				if (offspring[j].index == a[i].index)
		      	{
		      		present = true;
		      	}
			}

			if (!present)
			{
				offspring[i].index = a[i].index;
			} else {
				//See what can came here (what number).
				int outHelp = 1;
				for (int x = 1; x < countHelper+1; ++x)
				{
				  	if (offspring[x].index == outHelp)
				  	{
				  		outHelp = offspring[x].index + 1;
				  	}
				}
				offspring[i].index = outHelp;
			}
      	}
    }

    countHelper++;
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

void Population::introduceMutants(void) {
	int endIndex = floor((size / 4.0)); //End index when introducing mutants.

	//Reseting 25% of the population (introducing mutants).
	for (int i = 0; i < endIndex; ++i)
	{
		population[i].resetChromosome();
		population[i].setFitness(0.0);
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

	//Indexes of chromosomes to be overrided by mating result.
	for (int i = numMutants; i < (size - ceil((size / 2.0))); ++i)
	{
		int parentAIndex = rand() % ((size) - indexStartRand) + indexStartRand;
		int parentBIndex = rand() % ((size) - indexStartRand) + indexStartRand;

		while(parentBIndex == parentAIndex) {
			parentBIndex = rand() % ((size) - indexStartRand) + indexStartRand;
		}

		population[i].setResetGenes(matePair(population[parentAIndex].getChromosomeAsArray(), population[parentBIndex].getChromosomeAsArray()));
	}
}

/* Private methods */