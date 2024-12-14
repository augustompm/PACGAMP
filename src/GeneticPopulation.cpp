// GeneticPopulation.cpp
#include "GeneticPopulation.h"
#include "globals.h"
#include "utils.h"
#include "geneticOps.h"
GeneticPopulation::GeneticPopulation(TGraph&tGraph,int numNodes,int numDistricts){
attempts=0;
for(c=0;c<populationSize;c++){
TIndividual ind(numNodes,numDistricts);
centerDistrict=generateCenters(numNodes,numDistricts,tGraph.maxDistance);
if(centerDistrict.size()<(unsigned)numDistricts)break;
struct NodeCandidate{int node,grade;};
std::vector<NodeCandidate>cand;
for(p=0;p<numDistricts;p++){ind.addNode(p,centerDistrict[p]);ind.addDistrictSize(p);ind.addDistrictActivity(p,tGraph.tAdjList[centerDistrict[p]].nodeActivity[0],tGraph.tAdjList[centerDistrict[p]].nodeActivity[1]);}
while(ind.getIndividualSize()<numNodes){
bool addedNode=false;
for(p=0;p<numDistricts;p++){
for(unsigned int nn=0;nn<ind.chromossome[p].nodes.size();nn++){
int base=ind.chromossome[p].nodes[nn];
if(base>=0&&base<tGraph.numNodes){
TAdjListNode* run=tGraph.tAdjList[base].tOrigin;while(run){
int dest=run->destination;
if(dest>=0&&dest<tGraph.numNodes&&!ind.checkAssignedNode(dest)){
cand.push_back({dest,tGraph.getGrade(dest)});
}
run=run->next;}
}
}
std::sort(cand.begin(),cand.end(),[](NodeCandidate&a,NodeCandidate&b){return a.grade<b.grade;});
bool chosen=false;
for(unsigned int nn=0;nn<cand.size();nn++){
double g0=ind.getgVk0(p)+tGraph.getActivity0(cand[nn].node);
double g1=ind.getgVk1(p)+tGraph.getActivity1(cand[nn].node);
if(mi[0]>0&&mi[1]>0){
double limit0=mi[0]*(1+1*tau);
double limit1=mi[1]*(1+1*tau);
if(g0<limit0&&g1<limit1){
ind.addNode(p,cand[nn].node);ind.addDistrictActivity(p,tGraph.getActivity0(cand[nn].node),tGraph.getActivity1(cand[nn].node));ind.addDistrictSize(p);chosen=true;break;
}else{
if(attempts>(unsigned)numNodes*2){
ind.addNode(p,cand[nn].node);ind.addDistrictActivity(p,tGraph.getActivity0(cand[nn].node),tGraph.getActivity1(cand[nn].node));ind.addDistrictSize(p);chosen=true;break;
}
}
} else {
ind.addNode(p,cand[nn].node);ind.addDistrictActivity(p,tGraph.tAdjList[cand[nn].node].nodeActivity[0],tGraph.tAdjList[cand[nn].node].nodeActivity[1]);ind.addDistrictSize(p);chosen=true;break;
}
}
cand.clear();std::vector<NodeCandidate>(cand).swap(cand);
attempts++;
if(chosen){addedNode=true;break;}
}
if(!addedNode)break;
}
double distance;
for(p=0;p<numDistricts;p++){
double dist=0;
for(int n1=0;n1<(int)ind.chromossome[p].nodes.size();n1++){
for(int n2=0;n2<(int)ind.chromossome[p].nodes.size();n2++){
int N1=ind.chromossome[p].nodes[n1];
int N2=ind.chromossome[p].nodes[n2];
if(N1>=0&&(unsigned)N1<distances.size()&&N2>=0&&(unsigned)N2<distances[N1].size()){
double d=distances[N1][N2];
if(d>dist){dist=d;ind.chromossome[p].maxI=N1;ind.chromossome[p].maxJ=N2;}
}
}
}
ind.chromossome[p].fVk=dist;
}
ind.calcFS(tGraph.maxDistance);
ind.calcGS();
ind.calcFitness();
centerDistrict.clear();std::vector<int>(centerDistrict).swap(centerDistrict);
if(ind.getIndividualSize()==(int)numNodes)populationTIndividual.push_back(ind);
}
}
std::vector<TIndividual>GeneticPopulation::generateNew(TGraph&tGraph,int numNodes,int numDistricts){
attempts=0;std::vector<TIndividual>newPop;
for(c=0;c<populationSize;c++){
TIndividual ind(numNodes,numDistricts);
centerDistrict=generateCenters(numNodes,numDistricts,tGraph.maxDistance);
if(centerDistrict.size()<(unsigned)numDistricts)break;
struct NodeCandidate{int node,grade;};
std::vector<NodeCandidate>cand;
for(p=0;p<numDistricts;p++){ind.addNode(p,centerDistrict[p]);ind.addDistrictSize(p);ind.addDistrictActivity(p,tGraph.tAdjList[centerDistrict[p]].nodeActivity[0],tGraph.tAdjList[centerDistrict[p]].nodeActivity[1]);}
while(ind.getIndividualSize()<numNodes){
bool addedNode=false;
for(p=0;p<numDistricts;p++){
for(unsigned int nn=0;nn<ind.chromossome[p].nodes.size();nn++){
int base=ind.chromossome[p].nodes[nn];
if(base>=0&&base<tGraph.numNodes){
TAdjListNode* run=tGraph.tAdjList[base].tOrigin;while(run){
int dest=run->destination;
if(dest>=0&&dest<tGraph.numNodes&&!ind.checkAssignedNode(dest)){
cand.push_back({dest,tGraph.getGrade(dest)});
}
run=run->next;}
}
}
std::sort(cand.begin(),cand.end(),[](NodeCandidate&a,NodeCandidate&b){return a.grade<b.grade;});
bool chosen=false;
for(unsigned int nn=0;nn<cand.size();nn++){
double g0=ind.getgVk0(p)+tGraph.getActivity0(cand[nn].node);
double g1=ind.getgVk1(p)+tGraph.getActivity1(cand[nn].node);
if(mi[0]>0&&mi[1]>0){
double limit0=mi[0]*(1+1*tau);
double limit1=mi[1]*(1+1*tau);
if(g0<limit0&&g1<limit1){
ind.addNode(p,cand[nn].node);ind.addDistrictActivity(p,tGraph.getActivity0(cand[nn].node),tGraph.getActivity1(cand[nn].node));ind.addDistrictSize(p);chosen=true;break;
}else{
if(attempts>(unsigned)numNodes*2){
ind.addNode(p,cand[nn].node);ind.addDistrictActivity(p,tGraph.getActivity0(cand[nn].node),tGraph.getActivity1(cand[nn].node));ind.addDistrictSize(p);chosen=true;break;
}
}
} else {
ind.addNode(p,cand[nn].node);ind.addDistrictActivity(p,tGraph.getActivity0(cand[nn].node),tGraph.getActivity1(cand[nn].node));ind.addDistrictSize(p);chosen=true;break;
}
}
cand.clear();std::vector<NodeCandidate>(cand).swap(cand);
attempts++;
if(chosen){addedNode=true;break;}
}
if(!addedNode)break;
}
double distance;
for(p=0;p<numDistricts;p++){
double dist=0;
for(int n1=0;n1<(int)ind.chromossome[p].nodes.size();n1++){
for(int n2=0;n2<(int)ind.chromossome[p].nodes.size();n2++){
int N1=ind.chromossome[p].nodes[n1];
int N2=ind.chromossome[p].nodes[n2];
if(N1>=0&&(unsigned)N1<distances.size()&&N2>=0&&(unsigned)N2<distances[N1].size()){
double d=distances[N1][N2];
if(d>dist){dist=d;ind.chromossome[p].maxI=N1;ind.chromossome[p].maxJ=N2;}
}
}
}
ind.chromossome[p].fVk=dist;
}
ind.calcFS(tGraph.maxDistance);
ind.calcGS();
ind.calcFitness();
centerDistrict.clear();std::vector<int>(centerDistrict).swap(centerDistrict);
if(ind.getIndividualSize()==(int)numNodes)newPop.push_back(ind);
}
return newPop;
}
