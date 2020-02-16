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
  string lso = argv[5];
  int lsoIncrement = stoi(argv[6]);
  int twoOptIncrement = stoi(argv[7]);
  string bsPosition = argv[8];
  string bsPositionInit = argv[9];
  string printBest = argv[10];
  string sensors = argv[11];
  string instance = argv[12];

  bool debbug = true;

  double muleSpeed = 0.001;

  string instanceFileName = "./instances/bs-" + bsPosition + "/" + sensors + "/100-0/instance_dmsp_" + bsPositionInit + "_n" + sensors + "_r50_" + instance + ".dat.dat";
  string timeFormat = "s";

  solveDMSP_RKGA(popSize, maxInt, muleSpeed, instanceFileName, timeFormat, debbug, debuggLevel, totalExecutions, mating, lso, lsoIncrement, twoOptIncrement, printBest);

  return 0;
}
