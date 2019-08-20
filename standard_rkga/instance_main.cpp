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

  int popSize = 15; //Must be at least 4.
  int muleSpeed = 1.0;

  ifstream instance_file("instance_001.txt");
  Instance inst;
  consumeInstance(instance_file, &inst);
  cout << "\n> Finished processing .txt file\n\n";

  Population pop;

  //Initializing the initial population.
  pop.initializePopulation(popSize, inst.getNumberOfOriginalNodes());

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



  // pop.printPopulation();



  // pop.printPopulation();

  // cout << "\n*************************\n" << endl;






  // pop.printPopulation();

  // cout << "\n> " << inst.getNumberOfAEBP(5,3) << endl;
  // cout << "\n> " << inst.getDistanceBP(5,3) << endl;
  // cout << "\n> " << inst.getAExStartAxis(5,3,4) << endl;
  // cout << "\n> " << inst.getAEyStartAxis(5,3,4) << endl;
  // cout << "\n> " << inst.getAExEndAxis(5,3,4) << endl;
  // cout << "\n> " << inst.getAEyEndAxis(5,3,4) << endl;
  // cout << "\n> " << inst.getAELength(5,3,4) << endl;
  // cout << "\n> " << inst.getAENumberNodeCanBeServed(5,3,4) << endl;
  // if (inst.canXbeServedInAE(5,3,4,3))
  // {
  // 	cout << "\n> True" << endl;
  // } else {
  // 	cout << "\n> False" << endl;
  // }

  // SolutionStruct *solution;


  // for (size_t i = 0; i < genes.size(); i++) {
  //   double key = ((double) rand() / RAND_MAX);
  //   while (key == 1.0) {
  //     key = ((double) rand() / RAND_MAX);
  //   }
  //   genes[i] = key;
  // }

  // for (int i = 0; i < 6; ++i)
  // {
  //   SolutionStruct newSol;

  //   double key = ((double) rand() / RAND_MAX);
    
  //   while (key == 1.0) {
  //     key = ((double) rand() / RAND_MAX);
  //   }

  //   newSol.node = key;
  //   newSol.demand = inst.getNodesDemmand(i);

  //   solution[i] = newSol;
  // }

  // SolutionStruct newSol;

  // newSol.node = 0;
  // newSol.demand = 0;

  // solution[6] = newSol;

  // inst.evaluateSolution(solution, 1.0);

  // time(&end);

  // // Calculating total time taken by the program. 
  // double time_taken = double(end - start); 
  // cout << "Time taken by program is : " << fixed 
  //      << time_taken << setprecision(5); 
  // cout << " sec " << endl; 

  return 0;
}
