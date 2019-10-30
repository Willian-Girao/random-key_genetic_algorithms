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
void solveDMSP_RKGA(int popSize, int maxInt, double muleSpeed, string instanceFileName, string timeFormat, bool debbug, int debbugLevel, int totalExecution) {
  srand(time(0));
  
  clock_t time;
  time = clock();

  Instance inst;
  Population pop;
  double overallBest = -1.0;
  double averageSol = 0.0;
  double everageTime = 0.0;
  double localSearchPercent = 5.0;

  int executionsCount = 0;

  bool firstExecution = true;

  ifstream instance_file(instanceFileName);

  consumeInstance(instance_file, &inst);

  //Calculating instance demand.
  inst.setTotalDemand();

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
        pop.updateFitness(i, inst.evaluateSolution(pop.getSolutionAsArray(i), muleSpeed));
      }

      //Sorting by fitness.
      pop.sortByFitness();

      //Save best sol. thus far
      bestSolution = pop.getSingleChromosome(0).getFitness();

      //Introduce mutants.
      pop.introduceMutants();

      //Complete with offspring.
      pop.mateIndividuals();

      //Local search - provide percentage
      int totalSol = ceil((ceil((popSize / 2.0)) * localSearchPercent) / 100.0);
      int chromLength = pop.getSingleChromosome(0).getLength();

      if (j > 0 && j < 100)
      {
        for (int m = 0; m < totalSol; ++m)
        {
          double bestFit = pop.getSingleChromosome(m).getFitness();
          double newFit = bestFit;

          bool newInprovement = true;

          while (newInprovement)
          {
            newInprovement = false;

            for (int i = 2; i < (chromLength - 1) - 1; ++i)
            {
              for (int k = (i + 1); k < chromLength; ++k)
              {
                Hallele *current = pop.getSolutionAsArray(m);
                sortHalleleDecoder(current, chromLength);
                Hallele *newSol = twoOptSwapInner(current, i, k, chromLength);
                newFit = inst.evaluateSolution(newSol, muleSpeed);

                if (newFit < bestFit)
                {
                  cout << "\n\n2-Opt improvement: " << setprecision(10) << bestFit << " -> " << setprecision(10) << newFit << " iter: " << j << "\n\n";
                  newInprovement = true;
                  bestFit = newFit;
                  pop.updateSolutionHalleles(m, newSol);
                  break;
                }
              }

              if (newInprovement)
              {
                break;
              }
            }
          }
        }
      }

      //Checking termination criteria
      if (firstGen)
      {
        firstGen = false;
        previousBest = bestSolution;
      } else {
        if (bestSolution == previousBest)
        {
          genWithoutImprov++;
        } else {
          genWithoutImprov = 0;
        }
      }

      //Updating previous best
      previousBest = bestSolution;
    }

    //Updating fitness.
    for (int i = 0; i < popSize; ++i)
    {
      pop.updateFitness(i, inst.evaluateSolution(pop.getSolutionAsArray(i), muleSpeed));
    }

    //Sorting by fitness.
    pop.sortByFitness();

    time = clock() - time;

    //Printing best solution to screem.
    // inst.printFinalSolution(pop.getSingleChromosome(0).getChromosomeAsArray(), muleSpeed);
    cout << "\n\nFitness: " << setprecision(10) << pop.getSingleChromosome(0).getFitness() << endl;

    // //Calculating total time taken by the program. 
    double elapsed = 0.0;

    if (timeFormat == "ms") {
      elapsed = time;
      cout << "Execution time (ms): " << elapsed << endl << endl << endl;
      everageTime += elapsed;
    } else if (timeFormat == "s") {
      elapsed = (time * 1.0) / CLOCKS_PER_SEC;
      cout << "Execution time (s): " << elapsed << endl << endl << endl;
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

  cout << "===========================================\n\n";
  cout << "Instance: " << instanceFileName << endl;
  cout << "Total executions: " << totalExecution << endl << endl;
  cout << "Best solution: " << setprecision(10) << overallBest << endl;
  cout << "Avg. solution: " << setprecision(10) << avgSol << endl;
  cout << "Avg. time: " << setprecision(10) << avgTime << endl;
}
