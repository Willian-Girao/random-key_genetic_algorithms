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

int main() {

  int popSize = 20;
  int maxInt = 200;
  double muleSpeed = 0.001;
  int debuggLevel = 1;
  bool debbug = true;
  string instanceFileName = "instance_000.txt";
  string timeFormat = "s";

  solveDMSP_RKGA(popSize, maxInt, muleSpeed, instanceFileName, timeFormat, debbug, debuggLevel);

  return 0;
}
