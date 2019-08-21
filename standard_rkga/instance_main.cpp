/* Standard libraries */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <array>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>


#include "helper.cpp"

/* Headers containing classes definitions */
#include "instance_class.h"
#include "chromosome_class.h"
#include "population_class.h"

/* Cpp files containing classes implementations */
#include "instance_class.cpp"
#include "chromosome_class.cpp"
#include "population_class.cpp"

using namespace std;

int main() {
  srand(time(0));

  time_t start, end;
  time(&start);

  int popSize = 20; //Must be at least 4.
  int muleSpeed = 1.0;
  int maxInt = 50;

  ifstream instance_file("instance_002.txt");

  Instance inst;
  consumeInstance(instance_file, &inst);
  // cout << "\n> Finished processing .txt file\n\n";

  Population pop;

  //Initializing the initial population.
  pop.initializePopulation(popSize, inst.getNumberOfOriginalNodes());

  //Evolving.
  for (int x = 0; x < maxInt; ++x)
  {
    //Updating fitness.
    for (int i = 0; i < popSize; ++i)
    {
      pop.updateFitness(i, inst.evaluateSolution(pop.getSolutionAsArray(i), muleSpeed));
    }

    //Sorting by fitness.
    pop.sortByFitness();

    //Introduce mutants.
    pop.introduceMutants();

    //Complete with offspring.
    pop.mateIndividuals();

    // cout << x << endl;
  }

  //Updating fitness.
  for (int i = 0; i < popSize; ++i)
  {
    pop.updateFitness(i, inst.evaluateSolution(pop.getSolutionAsArray(i), muleSpeed));
  }

  //Sorting by fitness.
  pop.sortByFitness();

  // pop.printPopulation();

  time(&end);

  inst.printFinalSolution(pop.getSingleChromosome((popSize - 1)).getChromosomeAsArray(), muleSpeed);

  // Calculating total time taken by the program. 
  double time_taken = double(end - start); 
  cout << "Time taken by program is : " << fixed 
       << time_taken << setprecision(5); 
  cout << " sec " << endl; 

  return 0;
}
