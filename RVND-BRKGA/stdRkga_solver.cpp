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
  int maxInt = 4000;
  int debuggLevel = 1;
  int totalExecutions = 1;

  bool debbug = true;

  double muleSpeed = 0.001;

  // string instanceFileName = "./instances/bs-central/21/100-0/instance_dmsp_c_n21_r50_0.dat.dat";
  // string instanceFileName = "./instances/bs-central/6/100-0/instance_dmsp_c_n6_r50_0.dat.dat";
  // string instanceFileName = "./instances/bs-central/11/100-0/instance_dmsp_c_n11_r50_0.dat.dat";
  string instanceFileName = "./instances/bs-central/16/100-0/instance_dmsp_c_n16_r50_0.dat.dat";
  string timeFormat = "s";

  solveDMSP_RKGA(popSize, maxInt, muleSpeed, instanceFileName, timeFormat, debbug, debuggLevel, totalExecutions);

  return 0;
}
