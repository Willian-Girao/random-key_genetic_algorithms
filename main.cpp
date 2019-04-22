/* Standard libraries */
#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>

/* Headers containing classes definitions */
#include "chromosome_class.h"
#include "population_class.h"

/* Cpp files containing classes implementations */
#include "chromosome_class.cpp"
#include "population_class.cpp"

using namespace std;

int main() {
  srand (time(NULL));

  Population pop;
  Chromosome *elite;
  Chromosome *pair;

  elite = pop.getElite();
  pair = pop.getRandomPair();

  cout << endl;

  cout << "Elite 0: " << (*(elite)).getFitness() << endl;
  cout << "Elite 1: " << (*(elite + 1)).getFitness() << endl;

  cout << endl;

  cout << "Pair a: " << (*(pair)).getFitness() << endl;
  cout << "Pair b: " << (*(pair + 1)).getFitness() << endl;

  Chromosome offspring = pop.matePair((*(pair)), (*(pair + 1)));

  cout << endl;

  cout << "a: " << endl;
  (*(pair)).printGenes();

  cout << endl;

  cout << "b: " << endl;
  (*(pair + 1)).printGenes();

  cout << endl;

  cout << "offspring: " << endl;

  offspring.printGenes();

  // cout << endl;
  //
  // cout << a.getFitness() << endl;
  // cout << pop.gett(a) << endl;

  // Chromosome n = (*(elite));
  //
  // cout << "Copy: " << n.getFitness() << endl;

  return 0;
}
