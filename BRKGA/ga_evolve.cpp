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
void solveDMSP_RKGA(int popSize, int maxInt, double muleSpeed, string instanceFileName, string timeFormat, bool debbug, int debbugLevel, int totalExecution, string mating, string lso, int lsoIncrement, int twoOptIncrement, string printBest) {
  srand(time(0));

  double overallBest = -1.0;
  double averageSol = 0.0;
  double everageTime = 0.0;
  double localSearchPercent = 5.0;

  int executionsCount = 0;
  int noImproveCount = 0;

  bool firstExecution = true;

  Instance inst;
  Population pop;

  ifstream instance_file(instanceFileName);

  consumeInstance(instance_file, &inst);

  //Calculating instance demand.
  inst.setTotalDemand();

  clock_t time;

  int invalidCount = 0;
  int totalCount = 0;
  int lastMutant = popSize - floor((popSize / 4.0));
  int twoOptStartGen = 60;

  while(executionsCount < totalExecution)
  {
    //Initializing matric variables
    time = clock();

    //Initializing control varibles
    bool firstGen = true;

    double bestSolution = -1.0;
    double previousBest = -1.0;

    int genWithoutImprov = 0;
    int rvndKmax = 5;

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
        }
      }

      //Sorting by fitness.
      pop.sortByFitness();

      //Save best sol. thus far
      bestSolution = pop.getSingleChromosome(0).getFitness();

      //Show best (yes/no)
      if (printBest == "yes" && j < maxInt-1) {
        cout << setprecision(10) << bestSolution << endl;
      }

      /*-------------------------- 1. mutants --------------------------*/
      //Introduce mutants.
      pop.introduceMutants(); /* Standard BRKGA mutation */
      /*------------------------------------------------------------*/

      /*-------------------------- 2. mating --------------------------*/
      //Complete with offspring.
      if (mating == "default") {
        pop.mateIndividuals(&inst, muleSpeed, rvndKmax); /* BRKGA crossover (with local search - vnd/rvnd) */
      } else if (mating == "scc") {
        pop.sequentialConstructiveCrossover(&inst, muleSpeed, rvndKmax, mating); /* Sequential Constructive Crossover */
      } else if (mating == "hybrid") {
        // Uses the Sequential Constructive Crossover on the 1st quarter of the iterations, then the regular crossover.
        if (j < 5) {
          pop.sequentialConstructiveCrossover(&inst, muleSpeed, rvndKmax, mating);
        } else {
          pop.mateIndividuals(&inst, muleSpeed, rvndKmax);
        }
      }
      /*------------------------------------------------------------*/

      /*-------------------------- 3. local search --------------------------*/
      int lsCounter = 0;
      if (lso == "vnd") {
        while (lsCounter < popSize)
        {
          pop.vnd(lsCounter, &inst, muleSpeed);
          lsCounter += lsoIncrement;
        }
      } else if (lso == "rvnd") {
        while (lsCounter < popSize)
        {
          pop.rvnd(lsCounter, &inst, muleSpeed, rvndKmax);
          lsCounter += lsoIncrement;
        }
      }
      /*------------------------------------------------------------*/

      /*-------------------------- 3.1 local search --------------------------*/
      if (j >= twoOptStartGen) {
        int eliteLs = 0;
        int updatedCounter = 0;

        while (updatedCounter < 40 && eliteLs < lastMutant)
        {
          if (!pop.getTwoOptFlag(eliteLs))
          {
            pop.localSearch2Opt(eliteLs, &inst, muleSpeed); /* 2-Opt Local Search */
            updatedCounter++;
            eliteLs += twoOptIncrement;
          } else {
            eliteLs += 1;
          }
        }
      }
      /*------------------------------------------------------------*/

      /*-------------------------- 4. tracking stagnation --------------------------*/
      if (j > 0 && bestSolution == previousBest) {
        genWithoutImprov++;
      } else if (bestSolution < previousBest) {
        genWithoutImprov = 0;
        rvndKmax = 5;
      }

      if (genWithoutImprov >= 5) {
        if (j < twoOptStartGen && rvndKmax < 100) { //Depending only on local search 3.
          rvndKmax += 5;
        } else { //Stop steep increment - local search 3.1 kicks in
          if (j == twoOptStartGen) {
            rvndKmax = 0;
          }
          if (rvndKmax < 40) { //Towards the end increment must be limited
            rvndKmax += 5;
          }
        }
      }

      if (genWithoutImprov > 20) {
        break;
      }
      /*------------------------------------------------------------*/

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

    //End.
    time = clock() - time;

    //Calculating total time taken by the program.
    double elapsed = 0.0;

    if (timeFormat == "ms") {
      elapsed = time;
      // cout << "Execution time (ms): " << elapsed << endl << endl << endl;
      everageTime += elapsed;
    } else if (timeFormat == "s") {
      elapsed = (time * 1.0) / CLOCKS_PER_SEC;
      // cout << "Execution #" << executionsCount << " time: " << elapsed << endl;
      everageTime += elapsed;
    }

    //Updating average solution
    averageSol += pop.getSingleChromosome(0).getFitness();

    if (printBest == "yes") {
      cout << setprecision(10) << pop.getSingleChromosome(0).getFitness() << endl;
    }

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
  // cout << "Mating local search: " << ls << endl;
  cout << "Local search: " << lso << endl;
  cout << "2-Opt start generation: " << twoOptStartGen << endl;
  cout << "\nBest solution: " << setprecision(10) << overallBest << endl;
  cout << "Avg. solution: " << setprecision(10) << avgSol << endl;
  cout << "Avg. time: " << setprecision(10) << avgTime << endl;
  // cout << "Iterations without improvement: " << genWithoutImprov << endl;
  // cout << "Invalid solutions : " << setprecision(2) << ((invalidCount*100.0) / totalCount) << "\% (" << invalidCount << ")";
}
