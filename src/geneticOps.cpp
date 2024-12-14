// geneticOps.cpp
#include "geneticOps.h"
#include "utils.h"
#include "globals.h"
CheckRemoval::CheckRemoval(TGraph tGraph,std::vector<int>nodes,int p,int pos,int node){remove=false;pSize=(int)nodes.size();if(pSize>0&&pos>=0&&(unsigned)pos<nodes.size()){tGraph.setDistrict(node,-1);nodes.erase(nodes.begin()+pos);visited=singleDistrictBFS(tGraph,nodes,p);tGraph.setDistrict(node,p);}else{visited=0;}}
bool CheckRemoval::checkRemoval(){if(pSize>1&&visited==(pSize-1)){remove=true;return true;}return false;}
std::vector<int> generateCenters(int numNodes,unsigned int numDistricts,double maxDistance){std::vector<int>res;int attempts=0;while(res.size()<numDistricts&&attempts<100000){int randCenter=rand()%numNodes;bool ok=true;for(unsigned i=0;i<res.size();i++){if(distances[res[i]][randCenter]<=(maxDistance/9)){ok=false;break;}}if(ok)res.push_back(randCenter);attempts++;}
return res;}
int silentPrintBFS(const TGraph&tGraph,const TIndividual&tIndividual){int visited=0;for(int p=0;p<tGraph.numDistricts;p++){if(!tIndividual.chromossome[p].nodes.empty()){DistrictBFS db(tGraph.numNodes,p);int dh=tIndividual.chromossome[p].nodes[0];for(int n=0;n<(int)tIndividual.chromossome[p].nodes.size();n++){int cur=tIndividual.chromossome[p].nodes[n];if(cur>=0&&cur<tGraph.numNodes){TAdjListNode* run=tGraph.tAdjList[cur].tOrigin;while(run){int d1=tGraph.tAdjList[cur].district;int d2=tGraph.tAdjList[run->destination].district;if(d1==d2)db.addEdge(cur,run->destination);run=run->next;}}}visited+=db.silentBFS(dh);}}
return visited;}
int singleDistrictBFS(const TGraph&tGraph,std::vector<int>nodes,int p){if(nodes.empty())return 0;DistrictBFS db(tGraph.numNodes,p);int dh=nodes[0];for(int n=0;n<(int)nodes.size();n++){int cur=nodes[n];if(cur>=0&&cur<tGraph.numNodes){TAdjListNode* run=tGraph.tAdjList[cur].tOrigin;while(run){int d1=tGraph.tAdjList[cur].district;int d2=tGraph.tAdjList[run->destination].district;if(d1==d2)db.addEdge(cur,run->destination);run=run->next;}}}
return db.silentBFS(dh);}
void updateTGraphDistrics(TGraph&tGraph,const TIndividual&tIndividual){tGraph.resetDistricts();for(int p=0;p<tGraph.numDistricts;p++){for(int n=0;n<(int)tIndividual.chromossome[p].nodes.size();n++){int node=tIndividual.chromossome[p].nodes[n];if(node>=0&&node<tGraph.numNodes)tGraph.setDistrict(node,p);}}}
bool alreadyAssigned(double fitness,std::vector<TIndividual>selectedTIndividual){for(int c=0;c<(int)selectedTIndividual.size();c++){if(fabs(selectedTIndividual[c].fitness - fitness)<1e-12)return true;}return false;}
