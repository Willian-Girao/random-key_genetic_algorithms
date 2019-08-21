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

//Use a standar Random Key Genetic Algorithm to solve a Data Mule Scheduling Problem Instance.
// 'popSize': size of the population.
// 'maxInt': maximum number of iterations.
// 'muleSpeed': speed utilized by the mule.
// 'instanceFileName': name of the .txt file containing the graph instance.
void solveDMSP_RKGA(int popSize, int maxInt, int muleSpeed, string instanceFileName, string timeFormat) {
  srand(time(0));
  
  clock_t time;
  time = clock();

  Instance inst;
  Population pop;

  ifstream instance_file(instanceFileName);

  consumeInstance(instance_file, &inst);

  //Calculating instance demand.
  inst.setTotalDemand();

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
  }

  //Updating fitness.
  for (int i = 0; i < popSize; ++i)
  {
    pop.updateFitness(i, inst.evaluateSolution(pop.getSolutionAsArray(i), muleSpeed));
  }

  //Sorting by fitness.
  pop.sortByFitness();

  // pop.printPopulation();

  time = clock() - time;

  //Printing best solution to screem.
  inst.printFinalSolution(pop.getSingleChromosome((popSize - 1)).getChromosomeAsArray(), muleSpeed);

  //Calculating total time taken by the program. 
  double elapsed = 0.0;

  if (timeFormat == "ms") {
    elapsed = time;
    cout << "Execution time (ms): " << elapsed << endl;
  } else if (timeFormat == "s") {
    elapsed = (time * 1.0) / CLOCKS_PER_SEC;
    cout << "Execution time (s): " << elapsed << endl;
  }
}
