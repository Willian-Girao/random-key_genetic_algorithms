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

#include "ga_evolve.cpp"

using namespace std;

int main(int argc, char* argv[]) {

  int debuggLevel = 1;
  int totalExecutions = stoi(argv[1]);
  int maxInt = stoi(argv[2]);
  int popSize = stoi(argv[3]);
  string mating = argv[4];
  // string ls = argv[5];
  string lso = argv[5];
  int lsoIncrement = stoi(argv[6]);
  int twoOptIncrement = stoi(argv[7]);
  string sensors = argv[8];
  string instance = argv[9];
  string printBest = argv[10];

  bool debbug = true;

  double muleSpeed = 0.001;

  string instanceFileName = "./instances/bs-central/" + sensors + "/100-0/instance_dmsp_c_n" + sensors + "_r50_" + instance + ".dat.dat";
  string timeFormat = "s";

  solveDMSP_RKGA(popSize, maxInt, muleSpeed, instanceFileName, timeFormat, debbug, debuggLevel, totalExecutions, mating, lso, lsoIncrement, twoOptIncrement, printBest);

  return 0;
}
