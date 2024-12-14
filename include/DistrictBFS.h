// DistrictBFS.h
#pragma once
#include "globals.h"
class DistrictBFS{
public:
int size,district,c;std::list<int>* adjBFS;
DistrictBFS(int size,int district);
void addEdge(int source,int destination);
int bfs(int runningNode);
int silentBFS(int runningNode);
~DistrictBFS();
};
