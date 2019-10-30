/* Standard libraries */
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <array>
#include <stdlib.h>

using namespace std;

struct Hallele {
  double key;
  int index;
};

Hallele *twoOptSwapInner(Hallele *currentSol, int inputI, int inputK, int chromLength) {
	Hallele *newSol = new Hallele[chromLength];

	// 1. take currentSol[0] to currentSol[inputI-1] and add them in order to newSol
	for (int i = 0; i < (inputI - 1); ++i)
	{
		newSol[i].index = currentSol[i].index;
		newSol[i].key = currentSol[i].key;
	}

	// 2. take currentSol[inputI] to currentSol[inputK] and add them in reverse order to newSol
	for (int k = (inputK - 1); k >= (inputI - 1); --k)
	{
		int indx = (inputK - 1) - (k - (inputI - 1));

		newSol[indx].index = currentSol[k].index;
		newSol[indx].key = currentSol[k].key;
	}

	// 3. take currentSol[inputK+1] to chromLength and add them in order to newSol
	for (int x = inputK; x < chromLength; ++x)
	{
		newSol[x].index = currentSol[x].index;
		newSol[x].key = currentSol[x].key;
	}

	cout << "newSol [ ";
	for (int i = 0; i < chromLength; ++i)
	{
		cout << newSol[i].index << " ";
	}
	cout << " ] ";

	return newSol;
}

int main() {

	int chromLength = 9;

	//Example route: 0, 1, 2, 3, 4, 5, 6, 7, 0
	Hallele *h = new Hallele[chromLength];

	h[0].index = 0;
	h[0].key = 0.0;

	h[1].index = 1;
	h[1].key = 0.0;

	h[2].index = 2;
	h[2].key = 0.0;

	h[3].index = 3;
	h[3].key = 0.0;

	h[4].index = 4;
	h[4].key = 0.0;

	h[5].index = 5;
	h[5].key = 0.0;

	h[6].index = 6;
	h[6].key = 0.0;

	h[7].index = 7;
	h[7].key = 0.0;

	h[8].index = 0;
	h[8].key = 0.0;

	cout << "\n\n> Calculating 2-Opt...\n\n\n";

	cout << "\n\ncurSol [ A B C D E F G H A ]";
	cout << "\n\ncurSol [ ";
	for (int i = 0; i < chromLength; ++i)
	{
		cout << h[i].index << " ";
	}
	cout << " ]\n\n";

	//Number of nodes eligible to be swapped - 1 | 'i' starts as '2' as to leave start BS out
	for (int i = 2; i < (chromLength - 1) - 1; ++i)
	{
		//Number of nodes eligible to be swapped | '-1' to leave final BS out
		for (int k = (i + 1); k < chromLength; ++k)
		{
			Hallele *newSol = twoOptSwapInner(h, i, k, chromLength);
			cout << "i=" << i << " ,k=" << k << "\n\n";
		}
	}

	return 0;
}
















