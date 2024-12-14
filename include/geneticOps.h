// geneticOps.h
#pragma once
#include "globals.h"
#include "TGraph.h"
#include "TIndividual.h"
#include "DistrictBFS.h"
class CheckRemoval{
public:
int visited,pSize;bool remove;std::vector<int> nodes;
CheckRemoval(TGraph tGraph,std::vector<int>nodes,int p,int pos,int node);
bool checkRemoval();
};
std::vector<int> generateCenters(int numNodes,unsigned int numDistricts,double maxDistance);
int silentPrintBFS(const TGraph&tGraph,const TIndividual&tIndividual);
int singleDistrictBFS(const TGraph&tGraph,std::vector<int>nodes,int p);
void updateTGraphDistrics(TGraph&tGraph,const TIndividual&tIndividual);
bool alreadyAssigned(double fitness,std::vector<TIndividual>selectedTIndividual);
