/* Standard libraries */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <array>
#include <stdlib.h>
#include <time.h>


#include "helper.h"

/* Headers containing classes definitions */
#include "instance_class.h"

/* Cpp files containing classes implementations */
#include "instance_class.cpp"

using namespace std;

int main() {

  ifstream instance_file("instance_001.txt");
  string str;

  while(getline(instance_file, str)) {
    string parsed_line = "";
    int n_of_values = 0;
    double *values = new double[30];

    for(char& c : str) {
      parsed_line += isspace(c) ? ',' : c;
    }

    while(parsed_line != "") {
      string number = parsed_line.substr(0, parsed_line.find(","));
      parsed_line.erase(0, (number.length() + 1));

      (*(values + n_of_values)) = stod(number);
      n_of_values++;
    }

    /* Numerical content of the n-th line i the file */
    for (int i = 0; i < n_of_values; ++i)
    {
      cout << (*(values + i)) << endl;
    }
    cout << "--------------------------------------------" << endl;
    
  }

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
