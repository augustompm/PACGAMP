// TIndividual.cpp
#include "TIndividual.h"
#include "globals.h"
TIndividual::TIndividual(int numNodes,int numDistricts){this->numNodes=numNodes;this->numDistricts=numDistricts;this->individualSize=0;this->functionF=0;this->functionG=0;this->fitness=0;this->rank=999999;this->crowding=0;this->chromossome.resize(numDistricts);for(int p=0;p<numDistricts;p++){chromossome[p].fVk=0;chromossome[p].gVk[0]=0;chromossome[p].gVk[1]=0;chromossome[p].size=0;}}
void TIndividual::addDistrictSize(int p){if(p>=0&&p<numDistricts)chromossome[p].size++;}
void TIndividual::reduceDistrictSize(int p){if(p>=0&&p<numDistricts&&chromossome[p].size>0)chromossome[p].size--;}
void TIndividual::addDistrictActivity(int p,double meter,double readingTime){if(p>=0&&p<numDistricts){chromossome[p].gVk[0]+=meter;chromossome[p].gVk[1]+=readingTime;}}
void TIndividual::addIndividualSize(){individualSize++;}
void TIndividual::reduceIndividualSize(){if(individualSize>0)individualSize--;}
void TIndividual::removeDistrictActivity(int p,double meter,double readingTime){if(p>=0&&p<numDistricts){chromossome[p].gVk[0]-=meter;chromossome[p].gVk[1]-=readingTime;}}
void TIndividual::setDistance(int p,int maxI,int maxJ,double maxDistance){if(p>=0&&p<numDistricts){chromossome[p].maxI=maxI;chromossome[p].maxJ=maxJ;chromossome[p].fVk=maxDistance;}}
int TIndividual::getSize(int p){if(p>=0&&p<numDistricts)return chromossome[p].size;return 0;}
int TIndividual::getIndividualSize(){return individualSize;}
int TIndividual::getDistrict(int node){int d=-1;for(int p=0;p<numDistricts;p++){for(int n=0;n<(int)chromossome[p].nodes.size();n++){if(chromossome[p].nodes[n]==node)d=p;}}return d;}
int TIndividual::getFirstNode(int node){int p=getDistrict(node);if(p<0||p>=numDistricts)return node;if(!chromossome[p].nodes.empty())return chromossome[p].nodes[0];return node;}
double TIndividual::getgVk0(int p){if(p>=0&&p<numDistricts)return chromossome[p].gVk[0];return 0;}
double TIndividual::getgVk1(int p){if(p>=0&&p<numDistricts)return chromossome[p].gVk[1];return 0;}
void TIndividual::addNode(int source,int destination){if(source>=0&&source<numDistricts&&destination>=0&&destination<numNodes){individualSize++;chromossome[source].nodes.push_back(destination);}}
void TIndividual::calcFS(double maxDistance){if(numDistricts>0&&maxDistance>0){double f=0;for(int p=0;p<numDistricts;p++){f+=chromossome[p].fVk;}functionF=f/(numDistricts*maxDistance);}else{functionF=1e9;}}
void TIndividual::calcGS(){if(numDistricts>0&&mi[0]>0&&mi[1]>0){double g=0;for(int p=0;p<numDistricts;p++){for(int i=0;i<2;i++){g+=fabs(chromossome[p].gVk[i]-mi[i])/mi[i];}}functionG=g/numDistricts;}else{functionG=1e9;}}
void TIndividual::calcFitness(){fitness=lambda*functionF+(1-lambda)*functionG;}
bool TIndividual::checkAssignedNode(int node){for(int p=0;p<numDistricts;p++){for(int n=0;n<(int)chromossome[p].nodes.size();n++){if(chromossome[p].nodes[n]==node)return true;}}return false;}
bool TIndividual::checkContiguity(TGraph tGraph,int node,int p){if(p<0||p>=numDistricts)return false;bool cont=false;for(int n=0;n<(int)chromossome[p].nodes.size();n++){int cur=chromossome[p].nodes[n];if(cur>=0&&cur<tGraph.numNodes){TAdjListNode* run=tGraph.tAdjList[cur].tOrigin;while(run){if(run->destination==node){cont=true;break;}run=run->next;}if(cont)break;}}return cont;}
