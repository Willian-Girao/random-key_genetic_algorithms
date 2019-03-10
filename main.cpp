/* Standard libraries */
#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>

/* Headers containing classes definitions */
#include "chromosome_class.h"
#include "population_class.h"

/* Cpp files containing classes implementations */
#include "chromosome_class.cpp"
#include "population_class.cpp"

using namespace std;

int main() {
  srand (time(NULL));

  Population p;

  p.printFitness();
  p.getElite();

  return 0;
}
