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

  // inst.printPairsFromMainNode(5,0);
  // inst.printPairsFromMainNode(5,1);
  // inst.printPairsFromMainNode(5,2);
  // inst.printPairsFromMainNode(5,3);
  // inst.printPairsFromMainNode(5,4);
  // inst.printPairsFromMainNode(5,5);

  return 0;
}
