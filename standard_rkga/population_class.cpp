#include <iostream>
#include <array>
#include <stdlib.h>

#include "population_class.h"

using namespace std;

/* Public methods */

Population::Population(int popSize, int chromSize) {
  size = popSize;

  for (int i = 0; i < popSize; i++) {
    cout << "here4" << endl;
    Chromosome chromosome(chromSize);
    cout << "here5" << endl;
    population[i] = chromosome;
  }
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
  cout << "here" << endl;
  for (int i = 0; i < size; i++) {
    cout << "Vector " << i << endl;
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
