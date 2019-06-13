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

  cout << "\n> Finished processing .txt file\n\n";

  inst.printPairsRelatedInfo();

  cout << "\n> " << inst.getNumberOfAEBP(5,3) << endl;
  cout << "\n> " << inst.getDistanceBP(5,3) << endl;
  cout << "\n> " << inst.getAExStartAxis(5,3,4) << endl;
  cout << "\n> " << inst.getAEyStartAxis(5,3,4) << endl;
  cout << "\n> " << inst.getAExEndAxis(5,3,4) << endl;
  cout << "\n> " << inst.getAEyEndAxis(5,3,4) << endl;
  cout << "\n> " << inst.getAELength(5,3,4) << endl;
  cout << "\n> " << inst.getAENumberNodeCanBeServed(5,3,4) << endl;
  if (inst.canXbeServedInAE(5,3,4,3))
  {
  	cout << "\n> True" << endl;
  } else {
  	cout << "\n> False" << endl;
  }

  return 0;
}
