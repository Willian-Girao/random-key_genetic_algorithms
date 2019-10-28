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
  Hallele *aux = new Hallele[population[0].getLength()]; //Holds 'indexes' that can still be inserted

  //Initializing offspring and auxiliar struct
  offspring[0].key = 0.0;
  offspring[0].index = 0;
  aux[0].index = 0;

  for (int i = 1; i < population[0].getLength(); ++i)
  {
  	offspring[i].index = -1;
  	aux[i].index = i;
  }

  aux[population[0].getLength()-1].index = 0; //Invalidating last '0'

  // cout << "A: ";
  // for (int i = 0; i < population[0].getLength(); ++i)
  // {
  //   cout << a[i].index << " ";
  // }
  // cout << "\n\n";

  // cout << "B: ";
  // for (int i = 0; i < population[0].getLength(); ++i)
  // {
  //   cout << b[i].index << " ";
  // }
  // cout << "\n\n";

  // cout << "Auxiliar: ";
  // for (int i = 0; i < population[0].getLength(); ++i)
  // {
  //   cout << aux[i].index << " ";
  // }
  // cout << "\n\n";

  int countHelper = 0;
  int aBSfIndex = -1; // Sol. 'a' index of "final BS"
  int bBSfIndex = -1; // Sol. 'a' index of "final BS"

  //Generating offspring
  for (int i = 1; i < population[0].getLength(); i++) {
    prob = ((double) rand() / RAND_MAX); /* TODO - this probability should be proportional to the vectors fitness value */

    if (prob >= 0.5) {
    	//Trying to populate with parent 'a'
    	offspring[i].key = a[i].key;

    	//Checking wheter gene can be inserted (not present yet)
    	if (population[0].canInsertGene(offspring, a[i].index))
    	{
    		offspring[i].index = a[i].index;
    		population[0].removeGeneAt(aux, a[i].index); //Invalidating gene
    		if (a[i].index == 0)
    		{
    			aBSfIndex = i;
      		}
      } else {
      	//Trying to populate with parent 'b'
		if (population[0].canInsertGene(offspring, b[i].index))
		{
			offspring[i].index = b[i].index;
			population[0].removeGeneAt(aux, b[i].index); //Invalidating gene
			if (b[i].index == 0)
	      	{
	      		bBSfIndex = i;
	      	}
		} else {
			//Patching missing gene.
			population[0].complementMissingGene(offspring, aux, i);
		}	
      }
    } else {
    	//Trying to populate with parent 'b'
	    offspring[i].key = b[i].key;

	    //Checking wheter gene can be inserted (not present yet)
		if (population[0].canInsertGene(offspring, b[i].index))
	    {
      		offspring[i].index = b[i].index;
      		population[0].removeGeneAt(aux, b[i].index); //Invalidating gene
      		if (b[i].index == 0)
	      	{
	      		bBSfIndex = i;
	      	}
      	} else {
      		//Trying to populate with parent 'a'
			if (population[0].canInsertGene(offspring, a[i].index))
			{
				offspring[i].index = a[i].index;
				population[0].removeGeneAt(aux, a[i].index); //Invalidating gene
				if (a[i].index == 0)
		      	{
		      		aBSfIndex = i;
		      	}
			} else {
				//Patching missing gene.
				population[0].complementMissingGene(offspring, aux, i);
			}
      	}
    }

    countHelper++;
  }

  // cout << "Offspring: ";
  // for (int i = 0; i < population[0].getLength(); ++i)
  // {
  //   cout << offspring[i].index << " ";
  // }
  // cout << "\n\n";

  // int asds = 0;
  // cin >> asds;

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