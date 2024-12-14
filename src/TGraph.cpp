// TGraph.cpp
#include "TGraph.h"
#include "globals.h"
TGraph::TGraph(int numNodes,int numDistricts){this->numNodes=numNodes;this->numDistricts=numDistricts;this->maxDistance=0;tAdjList=new TAdjList[numNodes];for(int i=0;i<numNodes;i++){tAdjList[i].tOrigin=NULL;tAdjList[i].grade=0;tAdjList[i].frontier=0;tAdjList[i].district=-1;tAdjList[i].nodeActivity[0]=0;tAdjList[i].nodeActivity[1]=0;}}
TAdjListNode* TGraph::newAdjListNode(int destination){TAdjListNode* newNode=new TAdjListNode;newNode->destination=destination;newNode->next=NULL;return newNode;}
void TGraph::addEdge(int source,int destination){if(source<0||destination<0||source>=numNodes||destination>=numNodes)return;TAdjListNode* newNode=newAdjListNode(destination);newNode->next=tAdjList[source].tOrigin;addGrade(source);tAdjList[source].tOrigin=newNode;newNode=newAdjListNode(source);newNode->next=tAdjList[destination].tOrigin;addGrade(destination);tAdjList[destination].tOrigin=newNode;}
void TGraph::setCoords(int n,double coordX,double coordY){if(n>=0&&n<numNodes){tAdjList[n].coordX=(int)coordX;tAdjList[n].coordY=(int)coordY;}}
void TGraph::setDistrict(int n,int district){if(n>=0&&n<numNodes)tAdjList[n].district=district;}
void TGraph::addGrade(int n){if(n>=0&&n<numNodes){tAdjList[n].grade++;}}
double TGraph::getCoordX(int n){if(n>=0&&n<numNodes)return tAdjList[n].coordX;return 0;}
double TGraph::getCoordY(int n){if(n>=0&&n<numNodes)return tAdjList[n].coordY;return 0;}
int TGraph::getGrade(int p){if(p>=0&&p<numNodes)return tAdjList[p].grade;return 0;}
int TGraph::getDistrict(int p){if(p>=0&&p<numNodes)return tAdjList[p].district;return -1;}
void TGraph::calcMaxDist(){double distance=0;for(int i=0;i<numNodes;i++){vector<double> row;row.reserve(numNodes);for(int j=0;j<numNodes;j++){distance=sqrt((double)(tAdjList[i].coordX - tAdjList[j].coordX)*(tAdjList[i].coordX - tAdjList[j].coordX)+(tAdjList[i].coordY - tAdjList[j].coordY)*(tAdjList[i].coordY - tAdjList[j].coordY));row.push_back(distance);if(distance>maxDistance){maxDistance=distance;maxDI=i;maxDJ=j;}}distances.push_back(row);}}
double TGraph::getActivity0(int n){if(n>=0&&n<numNodes)return tAdjList[n].nodeActivity[0];return 0;}
double TGraph::getActivity1(int n){if(n>=0&&n<numNodes)return tAdjList[n].nodeActivity[1];return 0;}
void TGraph::setActivity(int n,int meters,int readingTime){if(n>=0&&n<numNodes){tAdjList[n].nodeActivity[0]=meters;tAdjList[n].nodeActivity[1]=readingTime;}}
void TGraph::setFrontier(){for(int n=0;n<numNodes;n++){tAdjList[n].frontier=0;TAdjListNode* objRun=tAdjList[n].tOrigin;while(objRun){int d1=tAdjList[n].district;int d2=tAdjList[objRun->destination].district;if(d1!=d2){tAdjList[n].frontier=1;break;}objRun=objRun->next;}}}
void TGraph::setAdjFrontier(int n){if(n<0||n>=numNodes)return;TAdjListNode* objRun=tAdjList[n].tOrigin;int d1=tAdjList[n].district;int frontierFlag=0;while(objRun){int d2=tAdjList[objRun->destination].district;if(d1!=d2){frontierFlag=1;break;}objRun=objRun->next;}tAdjList[n].frontier=frontierFlag;}
void TGraph::resetDistricts(){for(int n=0;n<numNodes;n++){tAdjList[n].district=-1;}}
void TGraph::printTGraph(){}
