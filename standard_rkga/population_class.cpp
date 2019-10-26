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

  int countHelper = 0;
  int aBSfIndex = -1; // Sol. 'a' index of "final BS"
  int bBSfIndex = -1; // Sol. 'a' index of "final BS"

  for (int i = 1; i < population[0].getLength(); i++) {
    prob = ((double) rand() / RAND_MAX); /* TODO - this probability should be proportional to the vectors fitness value */
    bool present = false;

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
      	if (a[i].index == 0)
      	{
      		aBSfIndex = i;
      	}
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
			if (b[i].index == 0)
	      	{
	      		bBSfIndex = i;
	      	}
		} else {
			//See what can came here (what number).
			int outHelp = 1;

			while (outHelp < (population[0].getLength() - 1)) {
				bool presentH = false;

				for (int x = 1; x < countHelper+1; ++x)
				{
				  	if (offspring[x].index == outHelp)
				  	{
				  		presentH = true;
				  	}
				}

				if (presentH)
				{
					outHelp++;
				} else {
					break;
				}
			}
			
			offspring[i].index = outHelp > (population[0].getLength() - 2) ? 0 : outHelp;
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
      		if (b[i].index == 0)
	      	{
	      		bBSfIndex = i;
	      	}
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
				if (a[i].index == 0)
		      	{
		      		aBSfIndex = i;
		      	}
			} else {
				//See what can came here (what number).
				int outHelp = 1;

				while (outHelp < (population[0].getLength() - 1)) {
					bool presentH = false;

					for (int x = 1; x < countHelper+1; ++x)
					{
					  	if (offspring[x].index == outHelp)
					  	{
					  		presentH = true;
					  	}
					}

					if (presentH)
					{
						outHelp++;
					} else {
						break;
					}
				}
				
				offspring[i].index = outHelp > (population[0].getLength() - 2) ? 0 : outHelp;
			}
      	}
    }

    countHelper++;
  }

  // Validating if "final BS" has been introduced
  if (aBSfIndex == -1 && bBSfIndex == -1)
  {
  	// cout << "\n\nNo final BS inserted\n\n";
  	// int pause = 0;
  	// cin >> pause;

  	for (int i = 0; i < population[0].getLength(); i++) {
  		if (b[i].index == 0)
      	{
      		bBSfIndex = i;
      	}

      	if (a[i].index == 0)
      	{
      		aBSfIndex = i;
      	}

      	prob = ((double) rand() / RAND_MAX);

	    if (prob >= 0.5) {
	    	offspring[aBSfIndex].index = 0;
	    	offspring[aBSfIndex].key = a[aBSfIndex].key;
	    } else {
	    	offspring[bBSfIndex].index = 0;
	    	offspring[bBSfIndex].key = b[bBSfIndex].key;
	    }
  	}
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
	int index = size - 1;

	//Reseting 25% of the population (introducing mutants).
	while(endIndex > 0)
	{
		// cout << "Solution " << index << " became a mutant.\n";
		population[index].resetChromosome();
		population[index].setFitness(0.0);

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

		population[i].setResetGenes(matePair(population[parentAIndex].getChromosomeAsArray(), population[parentBIndex].getChromosomeAsArray()));
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