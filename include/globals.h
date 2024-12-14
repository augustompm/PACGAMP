// globals.h
#pragma once
#include <time.h>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;
extern unsigned int mutation, populationSize, selectedPopulation, generations, resetLimit;
extern double mi[2], lambda, tau, tGraphArea;
extern vector<vector<double>> distances;
extern vector<vector<int>> tGraphConvexHull;
extern vector<vector<int>> sortedTGraphConvexHull;
extern vector<int> centerDistrict;
