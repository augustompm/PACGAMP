// TIndividual.h
#pragma once
#include "globals.h"
#include "TGraph.h"
struct CoordsXY{int x,y,p,np;};
struct Territory{int size,maxI,maxJ;double fVk,gVk[2],PISI;std::vector<int> nodes;};
class TIndividual{
public:
double fitness,functionF,functionG;
int numNodes,numDistricts,individualSize;
std::vector<Territory> chromossome;
int rank;
double crowding;
TIndividual(int numNodes,int numDistricts);
void addDistrictSize(int p);
void reduceDistrictSize(int p);
void addDistrictActivity(int p,double meter,double readingTime);
void addIndividualSize();
void reduceIndividualSize();
void removeDistrictActivity(int p,double meter,double readingTime);
void setDistance(int p,int maxI,int maxJ,double maxDistance);
int getSize(int p);
int getIndividualSize();
int getDistrict(int node);
int getFirstNode(int node);
double getgVk0(int p);
double getgVk1(int p);
void addNode(int source,int destination);
void calcFS(double maxDistance);
void calcGS();
void calcFitness();
bool checkAssignedNode(int node);
bool checkContiguity(TGraph tGraph,int node,int p);
};
