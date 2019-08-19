#include <iostream>
#include <array>
#include <stdlib.h>

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

/* Swapts to elements */
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
		// 'pi' is 'partitioning index', array[p] is now at the right position.
		int pi = partition(array, low, high);

		quickSort(array, low, (pi - 1));
		quickSort(array, (pi + 1), high);
	}
}


void Population::sortByFitness(void) {
  quickSort(population, 0, size - 1);
}

// Chromosome * Population::getElite(void) {
//   static Chromosome elite[2];

//   elite[0] = population[0];
//   elite[1] = population[1];

//   for (int i = 1; i < size; i++) {
//     if (population[i].getFitness() < elite[0].getFitness()) {
//       elite[1] = elite[0];
//       elite[0] = population[i];
//     } else if (population[i].getFitness() < elite[1].getFitness()) {
//       elite[1] = population[i];
//     }
//   }

//   cout << "Vector 0: " << elite[0].getFitness() << endl;
//   cout << "Vector 1: " << elite[1].getFitness() << endl;

//   return elite;
// }

// Chromosome * Population::getRandomPair(void) {
//   static Chromosome pair[2];

//   int p_a = rand() % 6;
//   int p_b = rand() % 6;

//   while (p_a == p_b) {
//     p_b = rand() % 6;
//   }

//   pair[0] = population[p_a];
//   pair[1] = population[p_b];

//   return pair;
// }

// Chromosome Population::matePair(Chromosome a, Chromosome b) {
//   double prob;
//   Chromosome offspring;

//   for (size_t i = 0; i < 5; i++) {
//     prob = ((double) rand() / RAND_MAX); /* TODO - this probability should be proportional to the vectors fitness value */

//     if (prob >= 0.5) {
//       offspring.genes[i] = a.getGene(i);
//     } else {
//       offspring.genes[i] = b.getGene(i);
//     }
//   }

//   return offspring;
// }

void Population::printPopulation(void) {
  for (int i = 0; i < size; i++) {
    cout << "Vector " << i << " (" << population[i].getFitness() << ")" << endl;
    population[i].printGenes();
    cout << endl;
  }
}

// void Population::printFitness(void) {
//   for (int i = 0; i < size; i++) {
//     cout << "Vector " << i << ": " << population[i].getFitness() << endl;
//   }
//   cout << endl;
// }

/* Private methods */

Hallele * Population::getSolutionAsArray(int solIndex) {
	return population[solIndex].getChromosomeAsArray();
}

void Population::updateFitness(int index, double fitness) {
	population[index].setFitness(fitness);
}

//TODO - BEST WOULD BE TO HAVE THE DEMAND WORKED OUT ONLY WHEN EVALUATING THE OBJ FUNCTION
// bool population::initializeUpdateDemand(int solInd, double demand) {
// 	for (int i = 0; i < count; ++i)
// 	{
// 		population[solInd].updateDemand(chronInd, demand);
// 	}
// }