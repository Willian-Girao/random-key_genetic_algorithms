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

  // inst.printInstanceMetadata();

  cout << "\n[ FINISHED PROCESSING .txt ]\n";

  inst.printPairsFromMainNode(1,0);
  inst.printPairsFromMainNode(1,1);
  inst.printPairsFromMainNode(1,2);
  inst.printPairsFromMainNode(1,3);
  inst.printPairsFromMainNode(1,4);
  inst.printPairsFromMainNode(1,5);

  // test(instance_file);
  // print(&inst);

  // inst.printSpeeds();
  // inst.setSpeed(0, 0.76);
  // inst.setSpeed(1, 23.56);
  // inst.printSpeeds();

  // inst.printNode(2);
  // inst.setNode(2, 150.01, 152.00, 21.0, 5.7, 14.5);
  // inst.printNode(2);

  return 0;
}
