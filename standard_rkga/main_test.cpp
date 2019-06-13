/* Standard libraries */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <array>
#include <stdlib.h>
#include <time.h>


#include "helper.cpp"

/* Headers containing classes definitions */
#include "instance_class.h"

/* Cpp files containing classes implementations */
#include "instance_class.cpp"

using namespace std;

int main() {
  ifstream instance_file("instance_001.txt");
  Instance inst;

  consumeInstance(instance_file, &inst);

  cout << "\n[ FINISHED PROCESSING .txt ]\n";

  // inst.printNode(0);
  // inst.printNode(5);

  inst.printPairsFromMainNode(0,0);
  inst.printPairsFromMainNode(0,1);
  inst.printPairsFromMainNode(0,2);
  inst.printPairsFromMainNode(0,3);
  inst.printPairsFromMainNode(0,4);
  inst.printPairsFromMainNode(0,5);

  inst.printPairsFromMainNode(1,0);
  inst.printPairsFromMainNode(1,1);
  inst.printPairsFromMainNode(1,2);
  inst.printPairsFromMainNode(1,3);
  inst.printPairsFromMainNode(1,4);
  inst.printPairsFromMainNode(1,5);

  inst.printPairsFromMainNode(2,0);
  inst.printPairsFromMainNode(2,1);
  inst.printPairsFromMainNode(2,2);
  inst.printPairsFromMainNode(2,3);
  inst.printPairsFromMainNode(2,4);
  inst.printPairsFromMainNode(2,5);

  inst.printPairsFromMainNode(3,0);
  inst.printPairsFromMainNode(3,1);
  inst.printPairsFromMainNode(3,2);
  inst.printPairsFromMainNode(3,3);
  inst.printPairsFromMainNode(3,4);
  inst.printPairsFromMainNode(3,5);

  inst.printPairsFromMainNode(4,0);
  inst.printPairsFromMainNode(4,1);
  inst.printPairsFromMainNode(4,3);
  inst.printPairsFromMainNode(4,3);
  inst.printPairsFromMainNode(4,4);
  inst.printPairsFromMainNode(4,5);

  inst.printPairsFromMainNode(5,0);
  inst.printPairsFromMainNode(5,1);
  inst.printPairsFromMainNode(5,2);
  inst.printPairsFromMainNode(5,3);
  inst.printPairsFromMainNode(5,4);
  inst.printPairsFromMainNode(5,5);

  return 0;
}
