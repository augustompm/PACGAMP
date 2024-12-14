// GeneticPopulation.h
#pragma once
#include "globals.h"
#include "TGraph.h"
#include "TIndividual.h"
class GeneticPopulation{
public:
int p,y;unsigned int n,c,attempts;
std::vector<TIndividual> populationTIndividual;
GeneticPopulation(TGraph&tGraph,int numNodes,int numDistricts);
std::vector<TIndividual> generateNew(TGraph&tGraph,int numNodes,int numDistricts);
};
