/* Standard libraries */
#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>

/* Headers containing classes definitions */
#include "chromosome_class.h"

/* Cpp files containing classes implementations */
#include "chromosome_class.cpp"

using namespace std;

int main() {
  Chromosome *list;

  list = new Chromosome[6];

  for (int i = 0; i < 6; ++i)
  {
  	Chromosome chrom;
  	list[i] = chrom;
  }

  // chrom.generateGenes(6);

  // chrom.printGenes();

  cout << " - " << endl;

  return 0;
}
