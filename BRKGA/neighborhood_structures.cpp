#include <time.h>
#include <iostream>
#include <array>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

/* Swap */
void nSwap(SolutionStruct *solution, int solLength) {
	solLength = solLength - 1;
	int swapA = rand() % solLength + 1;
	int swapB = rand() % solLength + 1;

	while(swapB == swapA)
	{
		swapB = rand() % solLength + 1; /* Random in [1, solLength] */
	}

	// cout << "\nswaping: " << swapA  << " for " << swapB << endl;

	int nodeTempA = solution[swapA].node;
	double demandTempA = solution[swapA].demand;

	solution[swapA].node = solution[swapB].node;
	solution[swapA].demand = solution[swapB].demand;

	solution[swapB].node = nodeTempA;
	solution[swapB].demand = demandTempA;
}

/* Shift */
void nShift(SolutionStruct *solution, int solLength) {
	solLength = solLength-1;
	int swapA = rand() % solLength + 1;
	int pos = rand() % solLength + 1;

	while(pos == swapA)
	{
		pos = rand() % solLength + 1; /* Random in [1, solLength] */
	}

	// cout << "\nshiffting: " << swapA  << " to pos. " << pos << endl;

	int posAuxNode = solution[pos].node;
	int posAuxDemand = solution[pos].demand;

	solution[pos].node = solution[swapA].node;
	solution[pos].demand = solution[swapA].demand;

	if (swapA < pos) {
		for (int i = pos-1; i >= swapA; i--) {
			int aux1 = solution[i].node;
			double aux2 = solution[i].demand;

			solution[i].node = posAuxNode;
			solution[i].demand = posAuxDemand;

			posAuxNode = aux1;
			posAuxDemand = aux2;
		}
	} else {
		for (int i = pos+1; i <= swapA; i++) {
			int aux1 = solution[i].node;
			double aux2 = solution[i].demand;

			solution[i].node = posAuxNode;
			solution[i].demand = posAuxDemand;

			posAuxNode = aux1;
			posAuxDemand = aux2;
		}
	}
}

/* Swap21 */
void nSwap21(SolutionStruct *solution, int solLength) {
	solLength = solLength-1;
	int swapA = rand() % solLength + 1;
	int swapB = rand() % solLength + 1;

	while(swapA == solLength)
	{
		swapA = rand() % solLength + 1; /* Random in [1, solLength] */
	}

	while(swapB == swapA || swapB == swapA+1)
	{
		swapB = rand() % solLength + 1; /* Random in [1, solLength] */
	}

	// cout << "\nswaping: " << swapA << " and " << swapA+1  << " for " << swapB << endl;

	if (swapA < swapB) {
		int nodeTempA = solution[swapA].node;
		double demandTempA = solution[swapA].demand;

		int nodeTempAplus = solution[swapA+1].node;
		double demandTempAplus = solution[swapA+1].demand;

		int nodeTempBminus = solution[swapB-1].node;
		double demandTempBminus = solution[swapB-1].demand;

		solution[swapA].node = solution[swapB].node;
		solution[swapA].demand = solution[swapB].demand;

		solution[swapB-1].node = nodeTempA;
		solution[swapB-1].demand = demandTempA;

		solution[swapB].node = nodeTempAplus;
		solution[swapB].demand = demandTempAplus;

		for (int i = swapB-2; i > swapA; i--) {
			int aux1 = solution[i].node;
			double aux2 = solution[i].demand;

			solution[i].node = nodeTempBminus;
			solution[i].demand = demandTempBminus;

			nodeTempBminus = aux1;
			demandTempBminus = aux2;
		}
	} else {
		int nodeTempB = solution[swapB].node;
		double demandTempB = solution[swapB].demand;

		int nodeTempBplus = solution[swapB+1].node;
		double demandTempBplus = solution[swapB+1].demand;

		solution[swapB].node = solution[swapA].node;
		solution[swapB].demand = solution[swapA].demand;

		solution[swapB+1].node = solution[swapA+1].node;
		solution[swapB+1].demand = solution[swapA+1].demand;

		solution[swapA+1].node = nodeTempB;
		solution[swapA+1].demand = demandTempB;

		for (int i = swapB+2; i < swapA+1; i++) {
			int aux1 = solution[i].node;
			double aux2 = solution[i].demand;

			solution[i].node = nodeTempBplus;
			solution[i].demand = demandTempBplus;

			nodeTempBplus = aux1;
			demandTempBplus = aux2;
		}
	}
}

void shiftFix(SolutionStruct *solution, int solLength, int swapA, int pos) {
	solLength = solLength-1;

	int posAuxNode = solution[pos].node;
	int posAuxDemand = solution[pos].demand;

	solution[pos].node = solution[swapA].node;
	solution[pos].demand = solution[swapA].demand;

	if (swapA < pos) {
		for (int i = pos-1; i >= swapA; i--) {
			int aux1 = solution[i].node;
			double aux2 = solution[i].demand;

			solution[i].node = posAuxNode;
			solution[i].demand = posAuxDemand;

			posAuxNode = aux1;
			posAuxDemand = aux2;
		}
	} else {
		for (int i = pos+1; i <= swapA; i++) {
			int aux1 = solution[i].node;
			double aux2 = solution[i].demand;

			solution[i].node = posAuxNode;
			solution[i].demand = posAuxDemand;

			posAuxNode = aux1;
			posAuxDemand = aux2;
		}
	}
}

// int main() {
//
// 	SolutionStruct *solution = new SolutionStruct[8];
//
//     solution[0].node = 0;
//     solution[0].key = 0.0;
//     solution[0].demand = 0;
//
//     solution[1].node = 2;
//     solution[1].key = 0.1;
//     solution[1].demand = 2;
//
//     solution[2].node = 3;
//     solution[2].key = 0.2;
//     solution[2].demand = 3;
//
//     solution[3].node = 1;
//     solution[3].key = 0.3;
//     solution[3].demand = 1;
//
//     solution[4].node = 5;
//     solution[4].key = 0.4;
//     solution[4].demand = 5;
//
//     solution[5].node = 0;
//     solution[5].key = 0.5;
//     solution[5].demand = 0;
//
//     solution[6].node = 6;
//     solution[6].key = 0.6;
//     solution[6].demand = 6;
//
// 		solution[7].node = 7;
//     solution[7].key = 0.7;
//     solution[7].demand = 7;
//
//     cout << "\n\n";
//     for (int i = 0; i < 8; ++i)
//     {
//     	cout << solution[i].node << " (" << solution[i].key << ") ";
//     }
//
//     nShift(solution, 8);
//     // nSwap(solution, 8);
//     // nSwap21(solution, 8);
//
//     cout << "\n\n";
//     for (int i = 0; i < 8; ++i)
//     {
//     	cout << solution[i].node << " (" << solution[i].key << ") ";
//     }
//
// 	return 0;
// }
