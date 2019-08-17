#include <bits/stdc++.h>

using namespace std;

struct Hallele {
	double key;
	int index;
};


/* Swapts to elements */
void swap(Hallele *a, Hallele *b) {
	Hallele temp = *a;
	*a = *b;
	*b = temp;
}

int partition(Hallele *array, int low, int high) {
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

void quickSort(Hallele *array, int low, int high) {
	if (low < high)
	{
		// 'pi' is 'partitioning index', array[p] is now at the right position.
		int pi = partition(array, low, high);

		quickSort(array, low, (pi - 1));
		quickSort(array, (pi + 1), high);
	}
}

void printArray(Hallele *array, int size) {
	for (int i = 0; i < size; ++i)
	{
		cout << array[i].key << " ";
	}
	cout << endl;
}

int main()  
{  
	Hallele h1;
	h1.key = 9.2;
	h1.index = 0;

	Hallele h2;
	h2.key = 1.3;
	h2.index = 1;

	Hallele h3;
	h3.key = 3.2;
	h3.index = 2;

    Hallele *chromosome;
    chromosome[0] = h1;
    chromosome[1] = h2;
    chromosome[2] = h3;

    for (int i = 0; i < 3; ++i)
    {
    	cout << chromosome[i].key << " ";
    }
    cout << endl;
    
    int n = 3;

    quickSort(chromosome, 0, n - 1);

    cout << "Sorted array: \n";

    printArray(chromosome, n);

    return 0;  
}