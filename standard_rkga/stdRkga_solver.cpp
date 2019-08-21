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
  int maxInt = 100;
  int muleSpeed = 1;
  string instanceFileName = "instance_002.txt";
  string timeFormat = "s";

  solveDMSP_RKGA(popSize, maxInt, muleSpeed, instanceFileName, timeFormat);

  return 0;
}
