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
  string ls = argv[4];
  string mating = argv[5];
  string sensors = argv[6];
  string instance = argv[7];

  bool debbug = true;

  double muleSpeed = 0.001;

  string instanceFileName = "./instances/bs-central/" + sensors + "/100-0/instance_dmsp_c_n" + sensors + "_r50_" + instance + ".dat.dat";
  string timeFormat = "s";

  solveDMSP_RKGA(popSize, maxInt, muleSpeed, instanceFileName, timeFormat, debbug, debuggLevel, totalExecutions, ls, mating);

  return 0;
}
