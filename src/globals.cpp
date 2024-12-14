// globals.cpp
#include "globals.h"
unsigned int mutation, populationSize, selectedPopulation, generations, resetLimit;
double mi[2], lambda=0.5f, tau, tGraphArea;
vector<vector<double>> distances;
vector<vector<int>> tGraphConvexHull;
vector<vector<int>> sortedTGraphConvexHull;
vector<int> centerDistrict;
