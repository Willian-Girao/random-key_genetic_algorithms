#include <bits/stdc++.h>

using namespace std;

/* Swapts to elements */
void swap(SolutionStruct *a, SolutionStruct *b) {
	SolutionStruct temp = *a;
	*a = *b;
	*b = temp;
}

int partition(SolutionStruct *array, int low, int high) {
	double pivot = array[high].key;
	int sml = (low - 1); // Smalest emelent's index.

	for (int i = low; i <= (high - 1); ++i)
	{
		if (array[i].key <= pivot)
		{			
			sml++;
			swap(&array[sml], &array[i]);
		}
	}

	swap(&array[sml + 1], &array[high]);
	return (sml + 1);
}

void quickSort(SolutionStruct *array, int low, int high) {
	if (low < high)
	{
		// 'pi' is 'partitioning index', array[p] is now at the right position.
		int pi = partition(array, low, high);

		quickSort(array, low, (pi - 1));
		quickSort(array, (pi + 1), high);
	}
}

/*
	DECODER - sorts the alleles as to have the key's indexes representing the final solution.
	Observation: sorting is only considering array from '1' to 'size - 2' (index '0' and 'size' must 
	always be base station for the DMSP - always generates valid solutions).
*/
void sortHalleleDecoder(SolutionStruct *chromosome, int n) {
    quickSort(chromosome, 0, n - 1);
}