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

#include "std_rkga_solver.cpp"

using namespace std;

int main(int argc, char* argv[]) {

  int popSize = 200;
  int maxInt = 3000;
  int debuggLevel = 1;
  int totalExecutions = 4;

  bool debbug = true;

  double muleSpeed = 0.001;

  string instanceFileName = "./instances/bs-central/21/100-0/instance_dmsp_c_n21_r50_0.dat.dat";
  string timeFormat = "s";

  solveDMSP_RKGA(popSize, maxInt, muleSpeed, instanceFileName, timeFormat, debbug, debuggLevel, totalExecutions);

  return 0;
}
