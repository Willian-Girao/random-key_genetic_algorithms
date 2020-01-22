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
#include <iomanip>

#include "helper.cpp"
#include "2opt.cpp"

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
void solveDMSP_RKGA(int popSize, int maxInt, double muleSpeed, string instanceFileName, string timeFormat, bool debbug, int debbugLevel, int totalExecution, string ls, string mating, string lso) {
  srand(time(0));

  double overallBest = -1.0;
  double averageSol = 0.0;
  double everageTime = 0.0;
  double localSearchPercent = 5.0;

  int executionsCount = 0;
  int noImproveCount = 0;
  int rvndKmax = 20;

  bool firstExecution = true;

  Instance inst;
  Population pop;

  ifstream instance_file(instanceFileName);

  consumeInstance(instance_file, &inst);

  //Calculating instance demand.
  inst.setTotalDemand();

  // int pause = 0;
  // inst.getGainAB(0, 3);
  // cin >> pause;

  clock_t time;
  time = clock();

  int invalidCount = 0;
  int totalCount = 0;

  while(executionsCount < totalExecution)
  {
    //Initializing control varibles
    bool firstGen = true;

    double bestSolution = -1.0;
    double previousBest = -1.0;

    int genWithoutImprov = 0;

    //Initializing the initial population.
    pop.initializePopulation(popSize, inst.getNumberOfOriginalNodes());

    //Evolving.
    for (int j = 0; j < maxInt; ++j)
    {
      //Updating fitness.
      for (int i = 0; i < popSize; ++i)
      {
        if (pop.shouldCalcFitness(i) || (pop.getSingleChromosome(i).getFitness() == 0.0))
        {
          pop.updateFitness(i, inst.evaluateSolution(pop.getSolutionAsArray(i), muleSpeed, false));
          pop.resetEvaluateFlag(i);

          // if (inst.isInvalidSolution(pop.getFitness(i))) {
          //   invalidCount++;
          //   pop.fixInvalidSolution(&inst, i, muleSpeed);
          // }
          // totalCount++;
        }
      }

      //Sorting by fitness.
      pop.sortByFitness();

      //Save best sol. thus far
      bestSolution = pop.getSingleChromosome(0).getFitness();

      // cout << j << " " << setprecision(10) << bestSolution << "\n";
      // cout << setprecision(10) << bestSolution << "\n";
      // cout << j << "\n";

      // if (bestSolution == previousBest) {
      //   noImproveCount++;
      //   if (noImproveCount > 9) {
      //     rvndKmax += 2;
      //   }
      // } else {
      //   noImproveCount = 0;
      //   rvndKmax = 20;
      // }

      //Introduce mutants.
      pop.introduceMutants(); /* Standard BRKGA mutation */

      //Complete with offspring.
      if (mating == "default") {
        pop.mateIndividuals(&inst, muleSpeed, ls, rvndKmax); /* BRKGA crossover (with local search - vnd/rvnd) */
      } else if (mating == "scc") {
        pop.sequentialConstructiveCrossover(&inst, muleSpeed, ls, rvndKmax); /* Sequential Constructive Crossover */
      }

      if (lso == "2-opt") {
        pop.localSearch2Opt(&inst, muleSpeed); /* 2-Opt Local Search */
      }

      //Updating previous best
      previousBest = bestSolution;
    }

    //Updating fitness.
    for (int i = 0; i < popSize; ++i)
    {
      if (pop.shouldCalcFitness(i) || (pop.getSingleChromosome(i).getFitness() == 0.0))
      {
        pop.updateFitness(i, inst.evaluateSolution(pop.getSolutionAsArray(i), muleSpeed, false));
      }
    }

    //Sorting by fitness.
    pop.sortByFitness();

    pop.localSearch2Opt(&inst, muleSpeed); /* 2-Opt Local Search */

    time = clock() - time;

    //Calculating total time taken by the program.
    double elapsed = 0.0;

    if (timeFormat == "ms") {
      elapsed = time;
      // cout << "Execution time (ms): " << elapsed << endl << endl << endl;
      everageTime += elapsed;
    } else if (timeFormat == "s") {
      elapsed = (time * 1.0) / CLOCKS_PER_SEC;
      // cout << "Execution time (s): " << elapsed << endl << endl << endl;
      everageTime += elapsed;
    }

    //Updating average solution
    averageSol += pop.getSingleChromosome(0).getFitness();

    //Executions/Experiments metrics
    if (firstExecution)
    {
      firstExecution = false;
      overallBest = pop.getSingleChromosome(0).getFitness();
    } else {
      if (pop.getSingleChromosome(0).getFitness() < overallBest)
      {
        overallBest = pop.getSingleChromosome(0).getFitness();
      }
    }

    //Next execution
    executionsCount++;
  }

  //Executions summary
  double avgSol = averageSol / totalExecution;
  double avgTime = everageTime / totalExecution;

  // cout << "===========================================\n\n";
  cout << "\nInstance: " << instanceFileName << endl;
  cout << "Total executions: " << totalExecution << endl;
  cout << "\nMating: " << mating << endl;
  cout << "Mating local search: " << ls << endl;
  cout << "Local search out: " << lso << endl;
  cout << "\nBest solution: " << setprecision(10) << overallBest << endl;
  cout << "Avg. solution: " << setprecision(10) << avgSol << endl;
  cout << "Avg. time: " << setprecision(10) << avgTime << endl;
  // cout << "Invalid solutions : " << setprecision(2) << ((invalidCount*100.0) / totalCount) << "\% (" << invalidCount << ")";
}
