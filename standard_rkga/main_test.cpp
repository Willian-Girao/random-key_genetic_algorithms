/* Standard libraries */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cctype>
#include <array>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h> 


#include "helper.cpp"

/* Headers containing classes definitions */
#include "instance_class.h"

/* Cpp files containing classes implementations */
#include "instance_class.cpp"

using namespace std;

int main() {
  time_t start, end;
  time(&start);

  ifstream instance_file("instance_001.txt");
  Instance inst;

  consumeInstance(instance_file, &inst);

  cout << "\n> Finished processing .txt file\n\n";

  inst.printPairsRelatedInfo();

  // cout << "\n> " << inst.getNumberOfAEBP(5,3) << endl;
  // cout << "\n> " << inst.getDistanceBP(5,3) << endl;
  // cout << "\n> " << inst.getAExStartAxis(5,3,4) << endl;
  // cout << "\n> " << inst.getAEyStartAxis(5,3,4) << endl;
  // cout << "\n> " << inst.getAExEndAxis(5,3,4) << endl;
  // cout << "\n> " << inst.getAEyEndAxis(5,3,4) << endl;
  // cout << "\n> " << inst.getAELength(5,3,4) << endl;
  // cout << "\n> " << inst.getAENumberNodeCanBeServed(5,3,4) << endl;
  // if (inst.canXbeServedInAE(5,3,4,3))
  // {
  // 	cout << "\n> True" << endl;
  // } else {
  // 	cout << "\n> False" << endl;
  // }

  SolutionStruct *solution;

  for (int i = 0; i < 6; ++i)
  {
    SolutionStruct newSol;

    newSol.node = i;
    newSol.demand = inst.getNodesDemmand(i);

    solution[i] = newSol;
  }

  SolutionStruct newSol;

  newSol.node = 0;
  newSol.demand = 0;

  solution[6] = newSol;

  // newSol.node = 2;
  // newSol.demand = inst.getNodesDemmand(2);

  // solution[1] = newSol;

  // newSol.node = 5;
  // newSol.demand = inst.getNodesDemmand(5);

  // solution[2] = newSol;

  // newSol.node = 1;
  // newSol.demand = inst.getNodesDemmand(1);

  // solution[5] = newSol;

  // newSol.node = 3;
  // newSol.demand = inst.getNodesDemmand(3);

  // solution[4] = newSol;

  // newSol.node = 4;
  // newSol.demand = inst.getNodesDemmand(4);

  // solution[3] = newSol;

  inst.evaluateSolution(solution, 1.0);

  time(&end);

  // Calculating total time taken by the program. 
  double time_taken = double(end - start); 
  cout << "Time taken by program is : " << fixed 
       << time_taken << setprecision(5); 
  cout << " sec " << endl; 

  return 0;
}
