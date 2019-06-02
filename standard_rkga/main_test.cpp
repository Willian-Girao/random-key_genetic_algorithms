/* Standard libraries */
#include <iostream>
#include <array>
#include <stdlib.h>
#include <time.h>

/* Headers containing classes definitions */
#include "instance_class.h"

/* Cpp files containing classes implementations */
#include "instance_class.cpp"

using namespace std;

int main() {

  /*
    3 - number of original nodes
    9 - number of total nodes after graphs pre-processing
    2 - number of allowed speeds
  */
  Instance inst(3, 9, 2);

  // inst.printSpeeds();
  // inst.setSpeed(0, 0.76);
  // inst.setSpeed(1, 23.56);
  // inst.printSpeeds();

  // inst.printNode(2);
  // inst.setNode(2, 150.01, 152.00, 21.0, 5.7, 14.5);
  // inst.printNode(2);

  return 0;
}
