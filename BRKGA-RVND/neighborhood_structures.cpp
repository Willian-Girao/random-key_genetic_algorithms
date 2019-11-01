#include <time.h>
#include <iostream>
#include <array>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

struct SolutionStruct { /* Structure used to evaluate the solution for the DMSP - Mr. Pablo's graph instance's structure based. */
    int node; //Node id.
    double key;
    double demand; //Node demand to be served.
};

/* Swapts to sensors within the sol. vector (considering both sensors inside and outside the route) */
void nSwap(SolutionStruct *solution, int solLength) {
	solLength = solLength - 1;
	int swapA = rand() % solLength + 1;
	int swapB = rand() % solLength + 1;

	while(swapB == swapA)
	{
		swapB = rand() % solLength + 1; /* Random in [1, solLength] */
	}

	// cout << "\n\nswapA: " << swapA << endl;
	// cout << "swapB: " << swapB << endl << endl;

	int nodeTempA = solution[swapA].node;
	double demandTempA = solution[swapA].demand;

	solution[swapA].node = solution[swapB].node;
	solution[swapA].demand = solution[swapB].demand;

	solution[swapB].node = nodeTempA;
	solution[swapB].demand = demandTempA;
}

void nShift(SolutionStruct *solution, int solLength) {
	int endIndex = -1;

	for (int i = 1; i < solLength; ++i)
	{
		if (solution[i].node == 0)
		{
			endIndex = i - 1; /* '-1' for rand function */
			break; 
		}
	}

	int targetIndex = rand() % endIndex + 1; /* Random in [1, endIndex] */
	int newPlaceIndex = rand() % endIndex + 1;

	while(newPlaceIndex == targetIndex)
	{
		newPlaceIndex = rand() % endIndex + 1;
	}

	/* Shifting elements */
	int curAuxNode = -1;
	double curAuxDemand = -1.0;

	targetIndex = 6;
	newPlaceIndex = 2;

	// cout << "\n\ntargetIndex: " << targetIndex << endl;
	// cout << "newPlaceIndex: " << newPlaceIndex << endl << endl;

	if (newPlaceIndex < targetIndex)
	{
		curAuxNode = solution[targetIndex].node;
		curAuxDemand = solution[targetIndex].demand;

		for (int i = targetIndex; i >= newPlaceIndex; --i)
		{
			if (i != newPlaceIndex)
			{
				solution[i].node = solution[(i - 1)].node;
				solution[i].demand = solution[(i - 1)].demand;
			} else {
				solution[i].node = curAuxNode;
				solution[i].demand = curAuxDemand;
			}
		}
	} else {
		for (int i = newPlaceIndex; i >= targetIndex; --i)
		{
			if (i == newPlaceIndex)
			{
				curAuxNode = solution[i].node;
				curAuxDemand = solution[i].demand;

				solution[i].node = solution[targetIndex].node;
				solution[i].demand = solution[targetIndex].demand;
			} 
			else {
				int curAuxNodeInner = solution[i].node;
				double curAuxDemandInner = solution[i].demand;

				solution[i].node = curAuxNode;
				solution[i].demand = curAuxDemand;

				curAuxNode = curAuxNodeInner;
				curAuxDemand = curAuxDemandInner;
			}
		}
	}
}

// int main() {

// 	SolutionStruct *solution = new SolutionStruct[7];

//     solution[0].node = 0;
//     solution[0].key = 0.0;
//     solution[0].demand = 0;

//     solution[1].node = 2;
//     solution[1].key = 0.1;
//     solution[1].demand = 2;

//     solution[2].node = 3;
//     solution[2].key = 0.2;
//     solution[2].demand = 3;

//     solution[3].node = 1;
//     solution[3].key = 0.3;
//     solution[3].demand = 1;

//     solution[4].node = 5;
//     solution[4].key = 0.4;
//     solution[4].demand = 5;

//     solution[5].node = 0;
//     solution[5].key = 0.5;
//     solution[5].demand = 0;

//     solution[6].node = 6;
//     solution[6].key = 0.6;
//     solution[6].demand = 6;

//     cout << "\n\n";
//     for (int i = 0; i < 7; ++i)
//     {
//     	cout << solution[i].node << " (" << solution[i].demand << " ) ";
//     }

//     // nShift(solution, 7);
//     nSwap(solution, 7);

//     cout << "\n\n";
//     for (int i = 0; i < 7; ++i)
//     {
//     	cout << solution[i].node << " (" << solution[i].demand << " ) ";
//     }

// 	return 0;
// }