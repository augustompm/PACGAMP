// TGraph.h
#pragma once
#include "globals.h"
struct TAdjListNode{int destination;TAdjListNode* next;};
struct TAdjList{int district,coordX,coordY,grade,frontier;double nodeActivity[2];TAdjListNode* tOrigin;};
class TGraph{
public:
int numNodes,numDistricts,maxDI,maxDJ;double maxDistance;TAdjList* tAdjList;
TGraph(int numNodes,int numDistricts);
TAdjListNode* newAdjListNode(int destination);
void addEdge(int source,int destination);
void setCoords(int n,double coordX,double coordY);
void setDistrict(int n,int district);
void addGrade(int n);
double getCoordX(int n);
double getCoordY(int n);
int getGrade(int p);
int getDistrict(int p);
void calcMaxDist();
double getActivity0(int n);
double getActivity1(int n);
void setActivity(int n,int meters,int readingTime);
void setFrontier();
void setAdjFrontier(int n);
void resetDistricts();
void printTGraph();
};
