#include <iostream>
#include <array>
#include <stdlib.h>
#include <math.h>
#include <limits>

#include "population_class.h"
#include "instance_class.h"
#include "utils.cpp"

#include "neighborhood_structures.cpp"

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

Hallele * Population::matePair(Hallele *a, double aFitness, Hallele *b, double bFitness) {
  double prob;

  Hallele *offspring = new Hallele[population[0].getLength()];

  //Initializing offspring
  offspring[0].index = 0;
  offspring[0].key = 0.0;
  for (int i = 1; i < population[0].getLength(); ++i)
  {
  	offspring[i].index = i;
  }
  offspring[population[0].getLength()-1].index = 0;

  double lowestKey = 2.0;
  int lowestKeySensor = 0;
  int lowestKeyIndex = 1;

  for (int i = 1; i < population[0].getLength(); i++)
  {
  	//Crossover gives priority to the parent with the best fitness value
    if (aFitness <= bFitness) //Parent 'a' has better fitness - biasing coin toss towards 'a'
    {
    	prob = ((double) rand() / RAND_MAX);

    	if (prob <= 0.7) //Parent 'a' won coin toss
    	{
	    	offspring[i].key = a[i].key;
	    	if (offspring[i].key < lowestKey)
	    	{
	    		lowestKey = offspring[i].key;
	    		lowestKeySensor = offspring[i].index;
	    		lowestKeyIndex = i;
	    	}
	    } else { //Parent 'b' won coin toss
		    offspring[i].key = b[i].key;
		    if (offspring[i].key < lowestKey)
	    	{
	    		lowestKey = offspring[i].key;
	    		lowestKeySensor = offspring[i].index;
	    		lowestKeyIndex = i;
	    	}
	    }
    } else { //Parent 'b' has better fitness - biasing coin toss towards 'b'
    	prob = ((double) rand() / RAND_MAX);

    	if (prob <= 0.7) //Parent 'b' won coin toss
    	{
	    	offspring[i].key = b[i].key;
	    	if (offspring[i].key < lowestKey)
	    	{
	    		lowestKey = offspring[i].key;
	    		lowestKeySensor = offspring[i].index;
	    		lowestKeyIndex = i;
	    	}
	    } else { //Parent 'a' won coin toss
		    offspring[i].key = a[i].key;
		    if (offspring[i].key < lowestKey)
	    	{
	    		lowestKey = offspring[i].key;
	    		lowestKeySensor = offspring[i].index;
	    		lowestKeyIndex = i;
	    	}
	    }
    }
  }

  if (lowestKeySensor == 0)
  {
    int swapA = (rand() % (population[0].getLength() - 2)) + 2;
    while (swapA == lowestKeyIndex)
    {
      swapA = (rand() % (population[0].getLength() - 2)) + 2;
    }

    double tempI = offspring[swapA].index;

    offspring[swapA].index = lowestKeySensor;

    offspring[lowestKeyIndex].index = tempI;
  }

  return offspring;
}

Hallele * Population::matePair004(Hallele *a, double aFitness, Hallele *b, double bFitness, Instance *inst, double muleVelocity) {
  double prob;

  Hallele *offspring = new Hallele[population[0].getLength()];

  //Initializing offspring
  offspring[0].index = 0;
  offspring[0].key = 0.0;
  for (int i = 1; i < population[0].getLength(); ++i)
  {
  	offspring[i].index = i;
  	offspring[i].key = a[i].key;
  }
  offspring[population[0].getLength()-1].index = 0;

  double aFit = 0.0;
  double bFit = 0.0;

  double lowestKey = 2.0;
  int lowestKeySensor = 0;
  int lowestKeyIndex = 1;

  for (int i = 1; i < population[0].getLength(); i++)
  {
  	offspring[i].key = a[i].key;
  	aFit = inst->evaluateSolution(offspring, muleVelocity, true);

  	offspring[i].key = b[i].key;
  	bFit = inst->evaluateSolution(offspring, muleVelocity, true);

  	if (aFit < bFit)
  	{
  		offspring[i].key = a[i].key;
  	}

  	if (offspring[i].key < lowestKey)
	{
		lowestKey = offspring[i].key;
		lowestKeySensor = offspring[i].index;
		lowestKeyIndex = i;
	}
  }

  if (lowestKeySensor == 0)
  {
    int swapA = (rand() % (population[0].getLength() - 2)) + 2;
    while (swapA == lowestKeyIndex)
    {
      swapA = (rand() % (population[0].getLength() - 2)) + 2;
    }

    double tempI = offspring[swapA].index;

    offspring[swapA].index = lowestKeySensor;

    offspring[lowestKeyIndex].index = tempI;
  }

  return offspring;
}

SolutionStruct * Population::matePairBRKGA02(Hallele *a, Hallele *b, Instance *inst, double muleVelocity) {
	SolutionStruct *parentA = inst->buildSolutionStructure(a);
  	SolutionStruct *parentB = inst->buildSolutionStructure(b);
  	SolutionStruct *currentBestSol = inst->buildSolutionStructure(a);

  	double usingAFit = 0.0;
  	double usingBFit = 0.0;
  	double crossoverFitness = 0.0;

  	int endingIndex = 0;
  	int pause = 0;

  	int choiceA = 0;
  	int choiceB = 0;
  	int lastDeletedAux = 0;
  	int lastDeletedAuxIndex = 0;

  	bool skipedOneBs = false;

  	int *aux = new int[population[0].getLength()-2];

  	for (int i = 0; i < population[0].getLength()-1; ++i)
  	{
    	aux[i] = i;
  	}

	cout << "Parent A: ";
	for (int i = 0; i < population[0].getLength(); ++i)
	{
		cout << parentA[i].node << " ";
	}
	cout << " | " << inst->evaluateBRKGA02Solution(parentA, muleVelocity, population[0].getLength(), false) << "\n\n";

	cout << "Parent B: ";
	for (int i = 0; i < population[0].getLength(); ++i)
	{
		cout << parentB[i].node << " ";
	}
	cout << " | " << inst->evaluateBRKGA02Solution(parentB, muleVelocity, population[0].getLength(), false) << "\n\n";

	cin >> pause;

	/* alph: create chromose using parent 'a' (index i):
	when i is a sensor within the current best
	mating result's route already (or when there's
	no more sensors after it), use the 1st 'legitimate
	sensor' from within {1,2,...,n}.
	*/
	currentBestSol[1].node = inst->checkCanInserSensor(currentBestSol, parentA[1].node, 1);
	/* finding selected's legitimate demand */
	for (int x = 0; x < population[0].getLength(); ++x)
	{
		if (parentA[x].node == currentBestSol[1].node)
		{
			currentBestSol[1].demand = parentA[x].demand;
			break;
		}
	}
	usingAFit = inst->evaluateBRKGA02Solution(currentBestSol, muleVelocity, 1+1, false);

  	/* bet: create chromose using parent 'b' (index i):
  	when i is a sensor within the current best
  	mating result's route already (or when there's
  	no more sensors after it), use the 1st 'legitimate
  	sensor' from within {1,2,...,n}.
  	*/
  	currentBestSol[1].node = inst->checkCanInserSensor(currentBestSol, parentB[1].node, 1);
  	/* finding selected's legitimate demand */
  	for (int x = 0; x < population[0].getLength(); ++x)
  	{
  		if (parentB[x].node == currentBestSol[1].node)
  		{
  			currentBestSol[1].demand = parentB[x].demand;
  			break;
  		}
  	}
  	usingBFit = inst->evaluateBRKGA02Solution(currentBestSol, muleVelocity, 1+1, false);

  	/* if cost of alph < bet, then current best mating
  	result receives alpah's index (bet's otherwise).
  	*/
  	if (usingAFit < usingBFit)
  	{
  		currentBestSol[1].node = inst->checkCanInserSensor(currentBestSol, parentA[1].node, 1);
	  	/* finding selected's legitimate demand */
	  	for (int x = 0; x < population[0].getLength(); ++x)
	  	{
	  		if (parentA[x].node == currentBestSol[1].node)
	  		{
	  			currentBestSol[1].demand = parentA[x].demand;
	  			break;
	  		}
	  	}
  	}

  	for (int k = 0; k < population[0].getLength()-1; ++k)
    {
      if (aux[k] == currentBestSol[1].node)
      {
      	lastDeletedAux = aux[k];
      	lastDeletedAuxIndex = k;
        aux[k] = -1;
        break;
      }
    }

    /* saving 1st selected (used) legitimate node */
    int currentLegitimateNode = currentBestSol[1].node;
    int nextSensorIndex = 0;
    int tempSensorIdHolder = 0;

    /* completing rest of legitimate nodes */
	for (int i = 2; i < population[0].getLength(); i++)
	{
		// cout << "\nOffspring: ";
		// for (int y = 0; y < i+1; ++y)
		// {
		//   cout << currentBestSol[y].node << " ";
		// }
		/* alph: create chromose using parent 'a' (index i):
		when i is a sensor within the current best
		mating result's route already (or when there's
		no more sensors after it), use the 1st 'legitimate
		sensor' from within {1,2,...,n}.
		*/
		/* finding next legitimate node on route for parent A */
    	nextSensorIndex = inst->findNextSensorOnRoute(parentA, currentLegitimateNode);
    	tempSensorIdHolder = nextSensorIndex == -1 ? -1 : parentA[nextSensorIndex].node;
		currentBestSol[i].node = inst->checkCanInserSensor(currentBestSol, tempSensorIdHolder, i);
		choiceA = currentBestSol[i].node;
		/* finding selected legitimate's demand */
		for (int x = 0; x < population[0].getLength(); ++x)
		{
			if (parentA[x].node == currentBestSol[i].node)
			{
				currentBestSol[i].demand = parentA[x].demand;
				break;
			}
		}
		// cout << "\nA before: ";
		// for (int y = 0; y < i+2; ++y)
		// {
		//   cout << currentBestSol[y].node << " ";
		// }
		if (choiceA != 0 && (i+1) < population[0].getLength())
		{
			currentBestSol[i+1].node = 0;
		}
		// cout << "\nA after: ";
		// for (int y = 0; y < i+2; ++y)
		// {
		//   cout << currentBestSol[y].node << " ";
		// }
		usingAFit = inst->evalSolFromSolStructure(currentBestSol, muleVelocity, true);
		// cout << "\nA fit.: " << usingAFit << endl;
		/*****************************************************************************************/

		/* bet: create chromose using parent 'b' (index i):
		when i is a sensor within the current best
		mating result's route already (or when there's
		no more sensors after it), use the 1st 'legitimate
		sensor' from within {1,2,...,n}.
		*/
		/* finding next legitimate node on route for parent B */
    	nextSensorIndex = inst->findNextSensorOnRoute(parentB, currentLegitimateNode);
    	tempSensorIdHolder = nextSensorIndex == -1 ? -1 : parentB[nextSensorIndex].node;
		currentBestSol[i].node = inst->checkCanInserSensor(currentBestSol, tempSensorIdHolder, i);
		choiceB = currentBestSol[i].node;
		/* finding selected legitimate's demand */
		for (int x = 0; x < population[0].getLength(); ++x)
		{
			if (parentB[x].node == currentBestSol[i].node)
			{
				currentBestSol[i].demand = parentB[x].demand;
				break;
			}
		}
		// cout << "\nB before: ";
		// for (int y = 0; y < i+2; ++y)
		// {
		//   cout << currentBestSol[y].node << " ";
		// }
		if (choiceB != 0 && (i+1) < population[0].getLength())
		{
			currentBestSol[i+1].node = 0;
		}
		// cout << "\nB after: ";
		// for (int y = 0; y < i+2; ++y)
		// {
		//   cout << currentBestSol[y].node << " ";
		// }
		usingBFit = inst->evalSolFromSolStructure(currentBestSol, muleVelocity, true);
		// cout << "\nB fit.: " << usingBFit << endl;
		// cin >> pause;
		/*****************************************************************************************/

		crossoverFitness = usingBFit;

		/* choosing best gene provider */
		if (usingAFit < usingBFit)
		{
			/* finding next legitimate node on route for parent A */
			currentBestSol[i].node = choiceA;
		  	/* finding selected's legitimate demand */
		  	for (int x = 0; x < population[0].getLength(); ++x)
		  	{
		  		if (parentA[x].node == currentBestSol[i].node)
		  		{
		  			currentBestSol[i].demand = parentA[x].demand;
		  			break;
		  		}
		  	}

		  	crossoverFitness = usingAFit;
		}

		/* updating remaining available genes */
		for (int k = 0; k < population[0].getLength()-1; ++k)
		{
			if (aux[k] == currentBestSol[i].node)
			{
				lastDeletedAux = aux[k];
      			lastDeletedAuxIndex = k;
				aux[k] = -1;
				break;
			}
		}

		/* if current best mating result already contains the
		final BS, return (updating fitness and completing the rest
		of the hallele).
		*/
		if (currentBestSol[i].node == 0)
		{
			endingIndex = i;
			break;
		}

		/* updating current legitimate node */
		currentLegitimateNode = currentBestSol[i].node;
	}

	if (endingIndex < population[0].getLength()-1 && endingIndex != 0)
	{
		int endingIndexAux = endingIndex;
		for (int i = 0; i < population[0].getLength()-1; ++i)
		{
			if (aux[i] != -1)
			{
				currentBestSol[endingIndexAux+1].node = aux[i];
				aux[i] = -1;
				endingIndexAux += 1;
			}
		}
	} else {
		currentBestSol[population[0].getLength()-1].node = 0;
	}

	cout << "\nOffspring: ";
	for (int y = 0; y < population[0].getLength(); ++y)
	{
	  cout << currentBestSol[y].node << " ";
	}
	cout << " | " << inst->evalSolFromSolStructure(currentBestSol, muleVelocity, false) << endl;
	// cout << "\n=============================================\n\n";
	// cin >> pause;

	delete[] aux;
	delete[] parentA;
	delete[] parentB;
	// delete[] currentBestSol;

	return currentBestSol;
}

void Population::insertNewGeneAt(SolutionStruct *sol, int indexEdit, int indexAux) {
	int tempNode = sol[indexAux].node; /* saving 10 */
	double tempKey = sol[indexAux].key;
	double tempDemand = sol[indexAux].demand;

	for (int i = indexAux; i > indexEdit; --i)
	{
		sol[i].node = sol[i-1].node;
		sol[i].key = sol[i-1].key;
		sol[i].demand = sol[i-1].demand;
	}

	sol[indexEdit].node = tempNode;
	sol[indexEdit].key = tempKey;
	sol[indexEdit].demand = tempDemand;
}

int Population::findeNextSensorIndexFromSensor(SolutionStruct *sol, int sensor, int size) {
	int index = 0;
	for (int i = 1; i < size; ++i)
	{
		if (sol[i].node == sensor)
		{
			index = i+1;
			break;
		}
	}

	if (index > size-1)
	{
		return 0;
	}


	return index;
}

SolutionStruct * Population::modularCrossover(Chromosome a, Chromosome b, Instance *inst, double muleVelocity) {
	SolutionStruct *parentA = inst->buildSolutionStructure(a.getChromosomeAsArray());
  	SolutionStruct *parentB = inst->buildSolutionStructure(b.getChromosomeAsArray());
  	SolutionStruct *currentBestSol;

  	int *aux = new int[population[0].getLength()-1];
  	for (int i = 0; i < population[0].getLength()-1; ++i)
  	{
    	aux[i] = i;
  	}
  	int pause = 0;

	// cout << "Parent A: ";
	// for (int i = 0; i < population[0].getLength(); ++i)
	// {
	// 	cout << parentA[i].node << " ";
	// }
	// cout << " | " << inst->evalSolFromSolStructure(parentA, muleVelocity, false) << "\n\n";

	// cout << "Parent B: ";
	// for (int i = 0; i < population[0].getLength(); ++i)
	// {
	// 	cout << parentB[i].node << " ";
	// }
	// cout << " | " << inst->evalSolFromSolStructure(parentB, muleVelocity, false) << "\n\n";

	if (a.getFitness() <= b.getFitness())
	{
		currentBestSol = inst->buildSolutionStructure(b.getChromosomeAsArray());

		for (int i = 1; i < population[0].getLength(); ++i)
	  	{
	    	for (int x = 1; x < population[0].getLength()-1; ++x)
	    	{
	    	 	if (aux[x] == parentB[i].node)
	    	 	{
	    	 		aux[x] = -1;
	    	 		break;
	    	 	}
	    	}

	    	if (parentB[i].node == 0)
	    	{
	    		break;
	    	}
	  	}
	} else {
		currentBestSol = inst->buildSolutionStructure(a.getChromosomeAsArray());
		for (int i = 1; i < population[0].getLength(); ++i)
	  	{
	    	for (int x = 1; x < population[0].getLength()-1; ++x)
	    	{
	    	 	if (aux[x] == parentA[i].node)
	    	 	{
	    	 		aux[x] = -1;
	    	 		break;
	    	 	}
	    	}

	    	if (parentA[i].node == 0)
	    	{
	    		break;
	    	}
	  	}
	}

	// cout << "Base sol.: ";
	// for (int i = 0; i < population[0].getLength(); ++i)
	// {
	// 	cout << currentBestSol[i].node << " ";
	// }
	// cout << "\n\n";

	// cout << "Aux: ";
	// for (int y = 0; y < population[0].getLength()-1; ++y)
	// {
	//   cout << aux[y] << " ";
	// }

	int baseNext = 0;
	int baseNextIndex = 0;
	int otherNext = 0;
	int otherParentsNext = 0;

	for (int i = 1; i < population[0].getLength()-1; ++i)
	{
		baseNextIndex = findeNextSensorIndexFromSensor(currentBestSol, currentBestSol[i].node, population[0].getLength());
		baseNext = currentBestSol[baseNextIndex].node;

		// cout << "\nCurrent: " << currentBestSol[i].node << endl;
		// cout << "baseNext: " << baseNext << endl;

		/* getting next eligible from the other parent (not the one generating the base solution) */
		if (a.getFitness() <= b.getFitness())
		{
			otherParentsNext = findeNextSensorIndexFromSensor(parentA, currentBestSol[i].node, population[0].getLength());
			// cout << otherParentsNext << endl;
			otherNext = otherParentsNext != 0 ? parentA[otherParentsNext].node : baseNext;
			// cout << "other's next: " << otherNext << endl;
		} else {
			otherParentsNext = findeNextSensorIndexFromSensor(parentB, currentBestSol[i].node, population[0].getLength());
			// cout << otherParentsNext << endl;
			otherNext = otherParentsNext != 0 ? parentB[otherParentsNext].node : baseNext;
			// cout << "other's next: " << otherNext << endl;
		}

		/* check if 'otherParentsNext' can be inserted */
		bool canInsert = false;
		for (int x = 0; x < population[0].getLength()-1; ++x)
		{
			if (aux[x] == otherNext)
			{
				canInsert = true;
			}
		}

		if (canInsert)
		{
			// cout << "sensor " << otherNext << " can be inserted\n\n";
			int targetIndex = 0;
			for (int y = 1; y < population[0].getLength(); ++y)
			{
				if (currentBestSol[y].node == otherNext)
				{
					targetIndex = y;
					break;
				}
			}

			insertNewGeneAt(currentBestSol, i+1, targetIndex);
			// cout << "updated sol.: ";
			// for (int i = 0; i < population[0].getLength(); ++i)
			// {
			// 	cout << currentBestSol[i].node << " ";
			// }
			// cout << "\n\n";

			for (int x = 1; x < population[0].getLength()-1; ++x)
			{
				if (aux[x] == otherNext)
				{
					aux[x] = -1;
					break;
				}
			}
			// cout << "Aux: ";
			// for (int y = 0; y < population[0].getLength()-1; ++y)
			// {
			//   cout << aux[y] << " ";
			// }
		} else {
			// cout << "sensor " << otherNext << " can NOT be inserted\n\n";
		}

		// cout << "\n=============================================\n\n";
		// cin >> pause;
	}
	// cout << "Base sol.: ";
	// for (int i = 0; i < population[0].getLength(); ++i)
	// {
	// 	cout << currentBestSol[i].node << " ";
	// }
	// cout << " | " << inst->evalSolFromSolStructure(currentBestSol, muleVelocity, false) << "\n";
	// cin >> pause;

	delete[] aux;
	delete[] parentA;
	delete[] parentB;
	// delete[] currentBestSol;

	return currentBestSol;
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
	// if (population[index].getFitness() == 0.0)
	// {
	// 	population[index].setFitness(fitness);
	// }
  population[index].setFitness(fitness);
}

void Population::resetEvaluateFlag(int index) {
	population[index].resetEvaluateFlag();
}

void Population::setEvaluateFlag(int index) {
	population[index].setEvaluateFlag();
}

bool Population::shouldCalcFitness(int index) {
	return population[index].shouldCalcFitness();
}

void Population::updateSolutionHalleles(int index, Hallele *newHallele) {
	population[index].setResetGenes(newHallele);
}

void Population::introduceMutants(void) {
	int endIndex = floor((size / 4.0)); //End index when introducing mutants.
	int index = size - 1;

	//Reseting 25% of the population (introducing mutants).
	while(endIndex > 0)
	{
		// cout << "Solution " << index << " became a mutant.\n";
		population[index].resetChromosome();
		// population[index].setFitness(0.0);
		population[index].setEvaluateFlag();

		index--;
		endIndex--;
	}
}

void Population::mutationBRKGA01(double mutationChoiceProb, double mutationBRKGA01Prob) {
	int endIndex = floor((size / 4.0)); //End index when introducing mutants.
	int index = size - 1;
	double prob = 0.0;

	//Reseting 25% of the population (introducing mutants).
	while(endIndex > 0)
	{
		prob = ((double) rand() / RAND_MAX);

		if (prob <= mutationChoiceProb)
		{
			population[index].resetChromosome();
			population[index].setFitness(0.0);
		} else {
			population[index].mutateBRKGA01(mutationBRKGA01Prob);
			population[index].setFitness(0.0);
		}

    population[index].setEvaluateFlag();

		index--;
		endIndex--;
	}
}

Chromosome Population::getSingleChromosome(int index) {
	return population[index];
}

double Population::getFitness(int index) {
	return population[index].getFitness();
}

void Population::mateIndividuals(Instance *inst, double muleVelocity, string ls, int rvndMax) {
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

		population[i].setResetGenes(matePair(population[parentAIndex].getChromosomeAsArray(), population[parentAIndex].getFitness(), population[parentBIndex].getChromosomeAsArray(), population[parentBIndex].getFitness()));
		population[i].setFitness(inst->evaluateSolution(population[i].getChromosomeAsArray(), muleVelocity, false));
    population[i].resetEvaluateFlag();

    // local search
    if (ls == "vnd") {
      vnd(i, inst, muleVelocity);
    } else if (ls == "rvnd") {
      rvnd(i, inst, muleVelocity, rvndMax);
    }
	}

	// int a;
	// cin >> a;
}

void Population::localSearch2Opt(int index, Instance *inst, double muleVelocity) {
  SolutionStruct *xprime = inst->buildSolutionStructure(population[index].getChromosomeAsArray());

  // cout << "\nx  { ";
  // for (int j = 0; j < population[0].getLength(); j++) {
  //   cout << xprime[j].node << " (" << setprecision(2) << xprime[j].key << ") ";
  // }
  // cout << " - " << population[0].getFitness() << endl;

  double fx = population[index].getFitness();
  double fxprime = fx;

  fxprime = twoOpt(xprime, inst, muleVelocity, fxprime);

  if (fxprime < fx) {
    // cout << "\n> improment";
    // update genes
    for (int y = 1; y < population[index].getLength(); y++) {
      population[index].updateKey(xprime[y].node, xprime[y].key);
    }
    // update fitness
    population[index].setFitness(fxprime);
    population[index].resetEvaluateFlag();
  }

  // SolutionStruct *v = inst->buildSolutionStructure(population[0].getChromosomeAsArray());
  // cout << "\nx' { ";
  // for (int j = 0; j < population[0].getLength(); j++) {
  //   cout << v[j].node << " (" << setprecision(2) << v[j].key << ") ";
  // }
  // cout << " - " << population[0].getFitness() << endl;
  //
  // cout << "\n\n> paused";
  // cin >> fx;

  delete[] xprime;
}

int Population::findAXFromA(SolutionStruct *solution, int a) {
  int next = -1;

  for (int i = 1; i < population[0].getLength(); ++i)
  {
    if (solution[i].node == a && i <= (population[0].getLength() - 2))
    {
      next = solution[i+1].node;
      break;
    }
  }

  return next;
}

void Population::sequentialConstructiveCrossover(Instance *inst, double muleVelocity, string ls, int rvndMax) {
	int numMutants = floor((size / 4.0));
	int x = size - ceil((size / 2.0)) - floor((size / 4.0));

	int indexStartRand = size - ceil((size / 2.0));
	int indexEndRand = size - 1;

  int pause = 0;
  int solVecSize = population[0].getLength();

	//Indexes of chromosomes to be overrided by mating result.
	for (int i = (size - numMutants - 1); i >= (size - ceil((size / 2.0))); --i)
	{
		int parentAIndex = rand() % (size / 2);
		int parentBIndex = rand() % (size / 2);

		while(parentBIndex == parentAIndex) {
			parentBIndex = rand() % (size / 2);
		}

    /* ======================= make sequential mutation here ======================= */
    // get parents as solution structure (sorted array)
    SolutionStruct *a = inst->buildSolutionStructure(population[parentAIndex].getChromosomeAsArray());
    SolutionStruct *b = inst->buildSolutionStructure(population[parentBIndex].getChromosomeAsArray());
    SolutionStruct *o = inst->buildSolutionStructure(population[i].getChromosomeAsArray());
    SolutionStruct *child = new SolutionStruct[solVecSize];
    int *sensorsLeftToUse = new int[solVecSize-2];

    for (int x = 0; x < solVecSize-2; x++) {
      sensorsLeftToUse[x] = x+1;
    }

    child[0].node = 0;
    child[0].demand = 0.0;
    child[0].key = 0.0;

    // cout << endl;
    // cout << "[a] - ";
    // for (int x = 0; x < solVecSize; x++) {
    //   cout << a[x].node << " (" << a[x].key << ") ";
    // }
    // cout << " { " << population[parentAIndex].getFitness();
    // cout << endl;
    // cout << "[b] - ";
    // for (int x = 0; x < solVecSize; x++) {
    //   cout << b[x].node << " (" << b[x].key << ") ";
    // }
    // cout << " { " << population[parentBIndex].getFitness();
    // cout << endl;
    // cout << "[o] - ";
    // for (int x = 0; x < solVecSize; x++) {
    //   cout << o[x].node << " (" << o[x].key << ") ";
    // }
    // cout << " { " << population[parentBIndex].getFitness();
    // cout << endl;

    // get final BS positions
    int aFBS = inst->findFinalBSIndex(a);
    int bFBS = inst->findFinalBSIndex(b);

    int lowestFBS = 0;
    int highestFBS = 0;
    int childFBS = 0;
    bool isLFBSInvalid = false;
    bool isHFBSInvalid = false;

    if (aFBS < bFBS) {
      lowestFBS = aFBS;
      highestFBS = bFBS;
      isLFBSInvalid = inst->isInvalidSolution(population[parentAIndex].getFitness());
      isHFBSInvalid = inst->isInvalidSolution(population[parentBIndex].getFitness());
    } else {
      lowestFBS = bFBS;
      highestFBS = aFBS;
      isLFBSInvalid = inst->isInvalidSolution(population[parentBIndex].getFitness());
      isHFBSInvalid = inst->isInvalidSolution(population[parentAIndex].getFitness());
    }

    // decide 1st sensor to go
    double aGain = inst->getGainAB(0, a[1].node, muleVelocity);
    double bGain = inst->getGainAB(0, b[1].node, muleVelocity);

    int aEqualCount = 1;
    int bEqualCount = 1;


    // updating 1st sensor to go
    if (aGain > bGain) {
      child[1].node = a[1].node;
      child[1].demand = a[1].demand;
      aEqualCount++;
    } else {
      child[1].node = b[1].node;
      child[1].demand = b[1].demand;
      bEqualCount++;
    }
    child[1].key = o[1].key; // doesn't matter which parent gives the key

    for (int y = 0; y < solVecSize-2; y++) {
      if (sensorsLeftToUse[y] == child[1].node) {
        sensorsLeftToUse[y] = -1;
        break;
      }
    }

    // cout << "\n1st selected: " << child[1].node << endl;

    int aNext = 0;
    int bNext = 0;
    int Xindex = 0;
    int lastAlteredIndex = 0;
    bool patchFinalBS = false;

    // deciding rest of sensors to go
    for (int x = 2; x < solVecSize; x++) {
      aNext = findAXFromA(a, child[x-1].node);
      bNext = findAXFromA(b, child[x-1].node);

      if ((aNext == -1) || (aNext == 0 && x <= lowestFBS && isLFBSInvalid) || (aNext == 0 && x <= highestFBS) || !inst->isntInSolution(child, aNext, x)) {
        // using auxiliar to find next sensor
        for (int y = 0; y < solVecSize-2; y++) {
          if (sensorsLeftToUse[y] != -1) {
            aNext = sensorsLeftToUse[y];
            // sensorsLeftToUse[y] = -1;
            break;
          }
        }
      }

      if ((bNext == -1) || (bNext == 0 && x <= lowestFBS && isLFBSInvalid) || (bNext == 0 && x <= highestFBS) || !inst->isntInSolution(child, bNext, x)) {
        // using auxiliar to find next sensor
        for (int y = 0; y < solVecSize-2; y++) {
          if (sensorsLeftToUse[y] != -1) {
            bNext = sensorsLeftToUse[y];
            // sensorsLeftToUse[y] = -1;
            break;
          }
        }
      }

      // cout << "\nA next: " << aNext << endl;
      // cout << "B next: " << bNext << endl;
      // cout << "(current): " << child[x-1].node << endl;

      aGain = inst->getGainAB(child[x-1].node, aNext, muleVelocity);
      bGain = inst->getGainAB(child[x-1].node, bNext, muleVelocity);

      // cout << "\nA gain: " << aGain << endl;
      // cout << "B gain: " << bGain << endl;

      // updating x-th sensor to go
      if (aGain > bGain) {
        child[x].node = aNext;
        child[x].demand = inst->getNodesDemmand(aNext);
      } else {
        child[x].node = bNext;
        child[x].demand = inst->getNodesDemmand(bNext);
      }
      child[x].key = o[x].key;

      if (child[x].node == a[x].node) {
        aEqualCount++;
      } else if (child[x].node == b[x].node) {
        bEqualCount++;
      }

      if (x == highestFBS && child[x].node != 0) {
        child[x].node = 0;
        child[x].demand = 0.0;
        childFBS = x;
        lastAlteredIndex = x;
        patchFinalBS = true;
        break;
      }

      if (child[x].node != 0) {
        for (int y = 0; y < solVecSize-2; y++) {
          if (sensorsLeftToUse[y] == child[x].node) {
            sensorsLeftToUse[y] = -1;
            break;
          }
        }
      }

      if (child[x].node == 0) {
        childFBS = x;
        for (int y = x+1; y < solVecSize; y++) {
          for (int w = 0; w < solVecSize-2; w++) {
            if (sensorsLeftToUse[w] != -1) {
              child[y].node = sensorsLeftToUse[w];
              child[y].demand = inst->getNodesDemmand(sensorsLeftToUse[w]);
              child[y].key = o[y].key;
              sensorsLeftToUse[w] = -1;
              break;
            }
          }
        }
        break;
      }
    }

    if (patchFinalBS) {
      for (int y = lastAlteredIndex+1; y < solVecSize; y++) {
        for (int w = 0; w < solVecSize-2; w++) {
          if (sensorsLeftToUse[w] != -1) {
            child[y].node = sensorsLeftToUse[w];
            child[y].demand = inst->getNodesDemmand(sensorsLeftToUse[w]);
            child[y].key = o[y].key;
            sensorsLeftToUse[w] = -1;
            break;
          }
        }
      }
    }

    double newFit = inst->evalSolFromSolStructure(child, muleVelocity, false);
    bool isChildInvalid = inst->isInvalidSolution(newFit);

    // cout << "[c] - ";
    // for (int x = 0; x < solVecSize; x++) {
    //   cout << child[x].node << " (" << child[x].demand << ") ";
    // }
    // cout << " { " << newFit << endl;

    if (isChildInvalid && childFBS < (solVecSize-1)) {
      // cout << "\nc is invalid\n";
      // cout << "c FBS: " << childFBS << endl;

      // utils_pause();

      int auxNode = 0;
      double auxDemand = 0.0;

      while (isChildInvalid && childFBS < (solVecSize-1)) {
        // temp saving node after current FBS position
        auxNode = child[childFBS+1].node;
        auxDemand = child[childFBS+1].demand;

        // swaping FBS with next position
        child[childFBS].node = auxNode;
        child[childFBS].demand = auxNode;

        child[childFBS+1].node = 0;
        child[childFBS+1].demand = 0.0;

        // reevaluating
        newFit = inst->evalSolFromSolStructure(child, muleVelocity, false);
        isChildInvalid = inst->isInvalidSolution(newFit);
        childFBS++;
      }
    } else if (!isHFBSInvalid) {
      bool improvement = true;
      int auxNode = 0;
      double auxDemand = 0.0;
      double fit = 0.0;

      // cout << "\nc room for improvement\n";
      // cout << "c FBS: " << childFBS << endl;

      // utils_pause();

      // try to fit FBS a position behind
      while (improvement && childFBS > 2) {
        // temp saving node right before current FBS position
        auxNode = child[childFBS-1].node;
        auxDemand = child[childFBS-1].demand;

        // swaping FBS with next position
        child[childFBS-1].node = 0;
        child[childFBS-1].demand = 0.0;

        child[childFBS].node = auxNode;
        child[childFBS].demand = auxDemand;

        // reevaluating
        fit = inst->evalSolFromSolStructure(child, muleVelocity, false);
        improvement = !inst->isInvalidSolution(fit);

        if (improvement) {
          // cout << "\n[ improved ]";
          childFBS--;
        } else {
          // cout << "\n[ no improvement ] { ";
          // cout << "\n[c'] - ";
          // for (int x = 0; x < solVecSize; x++) {
          //   cout << child[x].node << " (" << child[x].demand << ") ";
          // }
          // cout << " { " << fit << endl;

          // undo previous swap
          child[childFBS-1].node = auxNode;
          child[childFBS-1].demand = auxDemand;

          child[childFBS].node = 0;
          child[childFBS].demand = 0.0;
        }
      }
    }

    // cout << "[x] - ";
    // for (int x = 0; x < solVecSize; x++) {
    //   cout << child[x].node << " (" << child[x].demand << ") ";
    // }
    // cout << " { " << newFit << endl;

    for (int y = 1; y < solVecSize; y++) {
      population[i].updateKey(child[y].node, child[y].key);
    }
    population[i].setFitness(newFit);
    population[i].resetEvaluateFlag();


    // SolutionStruct *l = inst->buildSolutionStructure(population[i].getChromosomeAsArray());
    //
    // cout << "[c] - ";
    // for (int x = 0; x < solVecSize; x++) {
    //   cout << l[x].node << " (" << l[x].key << ") ";
    // }
    // cout << " { " << population[i].getFitness() << endl;
    //
    // int hl = 0;
    // cin >> hl;

    // local search
    if (ls == "vnd") {
      vnd(i, inst, muleVelocity);
    } else if (ls == "rvnd") {
      rvnd(i, inst, muleVelocity, rvndMax);
    }

    // freeing allocated memory
    delete[] a;
    delete[] b;
    delete[] o;
    delete[] child;
    delete[] sensorsLeftToUse;
	}
}

void Population::mateBRKGA02(Instance *inst, double muleVelocity) {
	int numMutants = floor((size / 4.0));
	int x = size - ceil((size / 2.0)) - floor((size / 4.0));

	int indexStartRand = size - ceil((size / 2.0));
	int indexEndRand = size - 1;

	SolutionStruct *matingResult = NULL;

	//Indexes of chromosomes to be overrided by mating result.
	for (int i = (size - numMutants - 1); i >= (size - ceil((size / 2.0))); --i)
	{
		int parentAIndex = rand() % (size / 2);
		int parentBIndex = rand() % (size / 2);

		while(parentBIndex == parentAIndex) {
			parentBIndex = rand() % (size / 2);
		}

		// cout << "==>\n";
		SolutionStruct *matingResult = matePairBRKGA02(population[parentAIndex].getChromosomeAsArray(), population[parentBIndex].getChromosomeAsArray(), inst, muleVelocity);
		// cout << "<--\n";

		for (int x = 1; x < population[0].getLength(); ++x)
		{
			// cout << matingResult[x].node << " (" << matingResult[x].key << ")\n";
			population[i].updateGenesSCX(matingResult[x].node, matingResult[x].key);
		}

		population[i].resetEvaluateFlag();

		// population[i].setFitness(inst->evaluateSolution(population[i].getChromosomeAsArray(), muleVelocity));

		// population[i].printGenes();

		// cout << "\nfit.: " << population[i].getFitness() << endl;

		// int pause = 0;
		// cin >> pause;

		delete[] matingResult;
	}
}

void Population::mateModularCrossover(Instance *inst, double muleVelocity) {
	int numMutants = floor((size / 4.0));
	int x = size - ceil((size / 2.0)) - floor((size / 4.0));

	int indexStartRand = size - ceil((size / 2.0));
	int indexEndRand = size - 1;

	SolutionStruct *matingResult = NULL;

	double bestFiness = 0;

	//Indexes of chromosomes to be overrided by mating result.
	for (int i = (size - numMutants - 1); i >= (size - ceil((size / 2.0))); --i)
	{
		int parentAIndex = rand() % (size / 2);
		int parentBIndex = rand() % (size / 2);

		while(parentBIndex == parentAIndex) {
			parentBIndex = rand() % (size / 2);
		}

		// cout << "==>\n";
		SolutionStruct *matingResult = modularCrossover(population[parentAIndex], population[parentBIndex], inst, muleVelocity);
		// cout << "<--\n";

		for (int x = 1; x < population[0].getLength(); ++x)
		{
			// cout << matingResult[x].node << " (" << matingResult[x].key << ")\n";
			population[i].updateGenesSCX(matingResult[x].node, matingResult[x].key);
		}

		// population[i].resetEvaluateFlag();

		population[i].setFitness(inst->evaluateSolution(population[i].getChromosomeAsArray(), muleVelocity, false));

		// if (population[parentAIndex].getFitness() <= population[parentBIndex].getFitness())
		// {
		// 	bestFiness = population[parentAIndex].getFitness();
		// } else {
		// 	bestFiness = population[parentBIndex].getFitness();
		// }

		// if (population[i].getFitness() <= bestFiness)
		// {
		// 	population[i].setResetGenes(matePair(population[parentAIndex].getChromosomeAsArray(), population[parentAIndex].getFitness(), population[parentBIndex].getChromosomeAsArray(), population[parentBIndex].getFitness()));
		// 	population[i].setEvaluateFlag();
		// }

		// population[i].printGenes();

		// cout << "\nA fit.: " << population[parentAIndex].getFitness() << endl;
		// cout << "\nB fit.: " << population[parentBIndex].getFitness() << endl;
		cout << "\nO fit.: " << population[i].getFitness() << endl;

		// int pause = 0;
		// cin >> pause;

		delete[] matingResult;
	}
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

void Population::vnd(int index, Instance *inst, double muleVelocity) {
  SolutionStruct *x = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
  SolutionStruct *xprime = inst->buildSolutionStructure(population[index].getChromosomeAsArray());

  double fx = population[index].getFitness();
  double fxprime = fx;

  // cout << "\n> vnd\n";
  // cin >> fx;

  int k = 0;
  int kmax = 3;

  int solLength = population[0].getLength();

  // cout << "x  { ";
  // for (int j = 0; j < solLength; j++) {
  //   cout << "[" << x[j].node << "]";
  // }
  // cout << " - " << fx << endl;

  while (k < kmax)
  {
    if (k == 0) {
      nShift(xprime, solLength);
    } else if (k == 1) {
      nSwap(xprime, solLength);
    } else if (k == 2) {
      nSwap21(xprime, solLength);
    }

    fxprime = inst->evalSolFromSolStructure(xprime, muleVelocity, false);

    if (fxprime < fx) {
      // cout << "\n> Improvement ";
      // if (k == 0) {
      //   cout << "(shift)\n";
      // } else if (k == 1) {
      //   cout << "(swap)\n";
      // } else if (k == 2) {
      //   cout << "(swap21)\n";
      // }
      // update better fintness
      fx = fxprime;
      // update genes
      for (int i = 1; i < solLength; i++) {
        x[i].node = xprime[i].node;
        x[i].demand = xprime[i].demand;
      }
      // cout << "x' { ";
      // for (int j = 0; j < solLength; j++) {
      //   cout << "[" << xprime[j].node << "]";
      // }
      // cout << " - " << fx << endl;
    } else {
      // reset x' to the previously x
      for (int i = 1; i < solLength; i++) {
        xprime[i].node = x[i].node;
        xprime[i].demand = x[i].demand;
      }
      // change neighborhood structure
      k++;
    }
  }

  if (fx < population[index].getFitness()) {
    // cout << "\nx  { ";
    // for (int j = 0; j < solLength; j++) {
    //   cout << "[" << x[j].node << "]";
    // }
    // cout << " - " << fx << endl;

    // update genes
    for (int y = 1; y < solLength; y++) {
      population[index].updateKey(x[y].node, x[y].key);
    }
    // update fitness
    population[index].setFitness(fx);
    population[index].resetEvaluateFlag();

    // cout << "\n\n> validation\n";
    // SolutionStruct *v = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
    // cout << "\nc  { ";
    // for (int j = 0; j < solLength; j++) {
    //   cout << "[" << v[j].node << "]";
    // }
    // cout << " - " << population[index].getFitness() << endl;
    //
    // cout << "\n\n> paused";
    // cin >> fx;
  }

  delete[] x;
  delete[] xprime;
}

void Population::rvnd(int index, Instance *inst, double muleVelocity, int rvndMax) {
  SolutionStruct *x = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
  SolutionStruct *xprime = inst->buildSolutionStructure(population[index].getChromosomeAsArray());

  double fx = population[index].getFitness();
  double fxprime = fx;

  // cout << "\n> rvnd " << rvndMax;
  // // cin >> fx;

  // int kmax = 4;
  int kmax = 3;
  int k = rand() % kmax;
  int lastk = k;

  int solLength = population[0].getLength();

  // cout << "x  { ";
  // for (int j = 0; j < solLength; j++) {
  //   cout << "[" << x[j].node << "]";
  // }
  // cout << " - " << fx << endl;

  int i = 0;
  while (i < rvndMax)
  {
    if (k == 0) {
      nShift(xprime, solLength);
    } else if (k == 1) {
      nSwap(xprime, solLength);
    } else if (k == 2) {
      nSwap21(xprime, solLength);
    }

    // else if (k == 3) {
    //   fxprime = twoOpt(xprime, inst, muleVelocity, fxprime);
    // }

    // if (k != 3) {
    //   fxprime = inst->evalSolFromSolStructure(xprime, muleVelocity, false);
    // }

    fxprime = inst->evalSolFromSolStructure(xprime, muleVelocity, false);

    if (fxprime < fx) {
      // update better fintness
      fx = fxprime;
      // update genes
      for (int i = 1; i < solLength; i++) {
        x[i].node = xprime[i].node;
        x[i].demand = xprime[i].demand;
      }
      i = 0;
    } else {
      // reset x' to the previously x
      for (int i = 1; i < solLength; i++) {
        xprime[i].node = x[i].node;
        xprime[i].demand = x[i].demand;
      }
      // change neighborhood structure
      k = rand() % kmax;
      // while (k == lastk) {
      //   k = rand() % kmax;
      // }
      // lastk = k;
      i++;
    }
  }

  if (fx < population[index].getFitness()) {
    // update genes
    for (int y = 1; y < solLength; y++) {
      population[index].updateKey(x[y].node, x[y].key);
    }
    // update fitness
    population[index].setFitness(fx);
    population[index].resetEvaluateFlag();
  }

  // cout << "\n\n> validation\n";
  // SolutionStruct *v = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
  // cout << "\nc  { ";
  // for (int j = 0; j < solLength; j++) {
  //   cout << "[" << v[j].node << "]" << v[j].demand;
  // }
  // cout << " - " << population[index].getFitness() << endl;
  //
  // cout << "\n\n> paused";
  // cin >> fx;

  delete[] x;
  delete[] xprime;
}

void Population::rvndLocalSearch(int index, Instance *inst, double muleVelocity, int rvndMax) {
  SolutionStruct *x = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
  SolutionStruct *xprime = inst->buildSolutionStructure(population[index].getChromosomeAsArray());

  double fx = population[index].getFitness();
  double fxprime = fx;

  // cout << "\n\n> max rvnd " << rvndMax << endl;

  int kmax = 3;
  int k = rand() % kmax;
  int lastk = k;

  int solLength = population[index].getLength();

  // cout << "x  { ";
  // for (int j = 0; j < solLength; j++) {
  //   cout << "[" << x[j].node << "]";
  // }
  // cout << " - " << fx << endl;

  int i = 0;
  while (i < rvndMax)
  {
    if (k == 0) {
      nShift(xprime, solLength);
    } else if (k == 1) {
      nSwap(xprime, solLength);
    } else if (k == 2) {
      nSwap21(xprime, solLength);
    }

    fxprime = inst->evalSolFromSolStructure(xprime, muleVelocity, false);

    if (fxprime < fx) {
      // cout << "\n[ improvement ]";
      // update better fintness
      fx = fxprime;
      // update genes
      for (int i = 1; i < solLength; i++) {
        x[i].node = xprime[i].node;
        x[i].demand = xprime[i].demand;
      }
      i = 0;
    } else {
      // reset x' to the previously x
      for (int i = 1; i < solLength; i++) {
        xprime[i].node = x[i].node;
        xprime[i].demand = x[i].demand;
      }
      // change neighborhood structure
      k = rand() % kmax;
      while (k == lastk) {
        k = rand() % kmax;
      }
      lastk = k;
      i++;
    }
  }

  if (fx < population[index].getFitness()) {
    // update genes
    for (int y = 1; y < solLength; y++) {
      population[index].updateKey(x[y].node, x[y].key);
    }
    // update fitness
    population[index].setFitness(fx);
    population[index].resetEvaluateFlag();
  }

  // cout << "\n\n> validation\n";
  // SolutionStruct *v = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
  // cout << "\nx' { ";
  // for (int j = 0; j < solLength; j++) {
  //   cout << "[" << v[j].node << "]";
  // }
  // cout << " - " << population[index].getFitness() << endl;
  //
  // cout << "\n\n> paused";
  // cin >> fx;

  delete[] x;
  delete[] xprime;
}

void Population::removeByGain(int index, Instance *inst, double muleVelocity) {
  SolutionStruct *x = inst->buildSolutionStructure(population[index].getChromosomeAsArray());

  int solLength = population[index].getLength();
  int finalBSIndex = 0;
  double fx = population[index].getFitness();

  cout << "x  { ";
  for (int j = 0; j < solLength; j++) {
    cout << "[" << x[j].node << "]";
  }
  cout << " - " << setprecision(10) << fx << endl;

  for (int i = 1; i < solLength; i++) {
    if (x[i+1].node == 0) {
      finalBSIndex = i+1;
      break;
    } else {
      cout << "\n> pair [" << x[i].node << " , " << x[i+1].node << "] - " << setprecision(10) << inst->getGainAB(x[i].node, x[i+1].node, muleVelocity);
    }
  }

  cout << "\n\n";

  for (int i = finalBSIndex+1; i < solLength-1; i++) {
    cout << "\n> pair [" << x[i].node << " , " << x[i+1].node << "] - " << setprecision(10) << inst->getGainAB(x[i].node, x[i+1].node, muleVelocity);
  }

  cout << "\n end index " << finalBSIndex;

  cout << "\n\n> paused";
  cin >> fx;

  // fxprime = inst->evalSolFromSolStructure(xprime, muleVelocity, false);


  // if (fx < population[index].getFitness()) {
  //   // update genes
  //   for (int y = 1; y < solLength; y++) {
  //     population[index].updateKey(x[y].node, x[y].key);
  //   }
  //   // update fitness
  //   population[index].setFitness(fx);
  //   population[index].resetEvaluateFlag();
  // }

  // cout << "\n\n> validation\n";
  // SolutionStruct *v = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
  // cout << "\nx' { ";
  // for (int j = 0; j < solLength; j++) {
  //   cout << "[" << v[j].node << "]";
  // }
  // cout << " - " << population[index].getFitness() << endl;
  //
  // cout << "\n\n> paused";
  // cin >> fx;

  delete[] x;
}

double Population::twoOpt(SolutionStruct *x, Instance *inst, double muleVelocity, double curFit) {
  SolutionStruct *xprime = NULL;

  double fx = curFit;
  double fxprime = fx;

  int solLength = population[0].getLength();

  // cout << "\ny  { ";
	// for (int j = 0; j < solLength; j++) {
	// 	cout << "[" << x[j].node << "]" << x[j].demand;
	// }
  // cout << " - " << fx << endl;

  // 2-Opt
  for (int i = 2; i < (solLength - 1); i++)
	{
    // cout << "\n> i outside " << i << endl;
		for (int k = (i + 1); k < solLength; ++k)
		{
			if (k != i+1)
      {
        xprime = twoOptLooop(x, solLength, i, k);
        fxprime = inst->evalSolFromSolStructure(xprime, muleVelocity, false);

        if (fxprime < fx)
        {
          // cout << "\n> improment\n";
          // cout << "\ny { ";
        	// for (int j = 0; j < solLength; j++) {
        	// 	cout << "[" << xprime[j].node << "]";
        	// }
          // cout << " - " << fxprime << endl;
          // cout << "i=" << i << ", k=" << k << endl;

          // update genes
          for (int i = 1; i < solLength; i++)
          {
            x[i].node = xprime[i].node;
            x[i].demand = xprime[i].demand;
          }
          // update better fintness
          fx = fxprime;
          // start again
          // cout << "\n> i inside " << i << endl;
          i = 1; // for loop will make it '2'
          break;
        }
			}
		}
	}
  // cout << "\n\n> paused";
  // cin >> fx;

  delete[] xprime;

  return fx;
}

void Population::fixInvalidSolution(Instance *inst, int index, double muleVelocity) {
  int finalBS = 0;
  int solLength = population[index].getLength();
  double curFitness = population[index].getFitness();
  // cout << "\n> sol length " << solLength;

  // SolutionStruct *x = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
  SolutionStruct *xprime = inst->buildSolutionStructure(population[index].getChromosomeAsArray());

  for (int i = 1; i < solLength; i++) {
    if (xprime[i].node == 0) {
      finalBS = i;
      break;
    }
  }

  // cout << "\n[befo.] { ";
  // for (int i = 0; i < solLength; i++) {
  //   cout << xprime[i].node << " [" << xprime[i].demand << "] " ;
  // }
  // cout << " - " << population[index].getFitness();

  // cout << "\n> final bs " << finalBS;

  double bestGain = 0.0;
  double gain = 0.0;
  int selectedIndex = 0;

  while (inst->isInvalidSolution(curFitness) && finalBS <= solLength-1) {
    for (int i = solLength-1; i > finalBS; i--) {
      gain = inst->getGainAB(xprime[finalBS-1].node, xprime[i].node, muleVelocity);
      if (gain > bestGain) {
        bestGain = gain;
        selectedIndex = i;
      }
    }

    // cout << "\n\n> best gain " << bestGain;
    // cout << "\n> selec index " << selectedIndex;

    shiftFix(xprime, solLength, selectedIndex, finalBS);
    curFitness = inst->evalSolFromSolStructure(xprime, muleVelocity, false);
    finalBS++;
    bestGain = 0.0;

    // cout << "\n[xxxxx] { ";
    // for (int i = 0; i < solLength; i++) {
    //   cout << xprime[i].node << " [" << xprime[i].demand << "] " ;
    // }
    // cout << " - " << curFitness;
  }

  // cout << "\n> final bs " << finalBS;

  // cout << "\n[afte.] { ";
  // for (int i = 0; i < solLength; i++) {
  //   cout << xprime[i].node << " [" << xprime[i].demand << "] " ;
  // }
  // cout << " - " << curFitness;

  for (int y = 1; y < solLength; y++) {
    population[index].updateKey(xprime[y].node, xprime[y].key);
  }
  population[index].setFitness(curFitness);

  // SolutionStruct *l = inst->buildSolutionStructure(population[index].getChromosomeAsArray());
  //
  // cout << "\n\n[check] { ";
  // for (int x = 0; x < solLength; x++) {
  //   cout << l[x].node << " [" << l[x].demand << "] ";
  // }
  // cout << " - " << population[index].getFitness() << endl;

  // cout << "\n\n> paused";
  //
  // int hl = 0;
  // cin >> hl;
  //
  // cin >> finalBS;
}
