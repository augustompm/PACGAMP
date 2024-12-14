// DistrictBFS.cpp
#include "DistrictBFS.h"
DistrictBFS::DistrictBFS(int size,int district){this->size=size;this->district=district;adjBFS=new std::list<int>[size];c=0;}
void DistrictBFS::addEdge(int source,int destination){if(source>=0&&source<size&&destination>=0&&destination<size)adjBFS[source].push_back(destination);}
int DistrictBFS::bfs(int runningNode){if(runningNode<0||runningNode>=size)return 0;int visitedNodes=1;bool* visited=new bool[size];for(int i=0;i<size;i++){visited[i]=false;}visited[runningNode]=true;std::list<int>q;q.push_back(runningNode);while(!q.empty()){runningNode=q.front();q.pop_front();for(auto it=adjBFS[runningNode].begin();it!=adjBFS[runningNode].end();++it){if(!visited[*it]){visitedNodes++;visited[*it]=true;q.push_back(*it);}}c=0;}delete[] visited;return visitedNodes;}
int DistrictBFS::silentBFS(int runningNode){if(runningNode<0||runningNode>=size)return 0;int visitedNodes=1;bool* visited=new bool[size];for(int i=0;i<size;i++)visited[i]=false;visited[runningNode]=true;std::list<int>q;q.push_back(runningNode);while(!q.empty()){runningNode=q.front();q.pop_front();for(auto it=adjBFS[runningNode].begin();it!=adjBFS[runningNode].end();++it){if(!visited[*it]){visitedNodes++;visited[*it]=true;q.push_back(*it);}}c=0;}delete[] visited;return visitedNodes;}
DistrictBFS::~DistrictBFS(){delete[] adjBFS;}
