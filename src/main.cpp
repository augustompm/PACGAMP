// main.cpp
#include "globals.h"
#include "utils.h"
#include "TGraph.h"
#include "TIndividual.h"
#include "GeneticPopulation.h"
#include "DistrictBFS.h"
#include "geneticOps.h"
#include "NSGAII.h"
#include "geneticGenerations.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>

int main(int argc,char* argv[]){
    if(argc<7)return 0;
    mutation=(unsigned)atoi(argv[1]);
    populationSize=(unsigned)atoi(argv[2]);
    float selectedPercent=(float)atoi(argv[3]);
    generations=(unsigned)atoi(argv[4]);
    resetLimit=(unsigned)atoi(argv[5]);
    std::string file=argv[6];
    float calcSelected=(float)populationSize*(selectedPercent/100.0f);
    selectedPopulation=(unsigned)(calcSelected*2);
    if(selectedPopulation%2==1)selectedPopulation+=1;
    srand((unsigned)time(0));
    std::ifstream inData(file.c_str());
    if(!inData.is_open())return 0;
    double header[5];
    for(int cc=0;cc<5;cc++){
        if(!(inData>>header[cc]))return 0;
    }
    int numNodes=(int)header[0];
    int numEdges=(int)header[1];
    int numDistricts=(int)header[2];
    lambda=header[3];
    tau=header[4];
    if(numNodes<=0||numEdges<0||numDistricts<=0)return 0;
    TGraph tGraph(numNodes,numDistricts);
    TIndividual tIndividual(numNodes,numDistricts);
    skipLines(inData,1);
    int c=0;
    double coordX,coordY,meters,readingTime,district;
    for(;c<numNodes;c++){
        if(!(inData>>coordX>>coordY>>meters>>readingTime>>district))break;
        int d=(int)district;
        if(d<0||d>=numDistricts)d=rand()%numDistricts;
        tGraph.setCoords(c,coordX,coordY);
        tGraph.setDistrict(c,d);
        tGraph.setActivity(c,(int)meters,(int)readingTime);
        tIndividual.addNode(d,c);
        tIndividual.addDistrictSize(d);
        tIndividual.addDistrictActivity(d,meters,readingTime);
        addActivity(meters,readingTime);
    }
    skipLines(inData,1);
    int ecount=0;
    double edgeA,edgeB;
    for(;ecount<numEdges;ecount++){
        if(!(inData>>edgeA>>edgeB))break;
        int a=(int)edgeA;int b=(int)edgeB;
        tGraph.addEdge(a,b);
    }
    inData.close();
    miCalc(numDistricts);
    tGraph.calcMaxDist();
    tGraph.setFrontier();
    GeneticPopulation geneticPopulation(tGraph,numNodes,numDistricts);
    if(geneticPopulation.populationTIndividual.empty()){
        for(unsigned p=0;p<populationSize;p++){
            TIndividual ind(numNodes,numDistricts);
            for(int node=0;node<numNodes;node++){
                int d=rand()%numDistricts;
                ind.addNode(d,node);
                ind.addDistrictSize(d);
                ind.addDistrictActivity(d,tGraph.getActivity0(node),tGraph.getActivity1(node));
            }
            for(int pp=0;pp<numDistricts;pp++){
                double dist=0;
                for(int n1=0;n1<(int)ind.chromossome[pp].nodes.size();n1++){
                    for(int n2=0;n2<(int)ind.chromossome[pp].nodes.size();n2++){
                        int N1=ind.chromossome[pp].nodes[n1];
                        int N2=ind.chromossome[pp].nodes[n2];
                        if(N1>=0&&(unsigned)N1<distances.size()&&N2>=0&&(unsigned)N2<distances[N1].size()){
                            double dd=distances[N1][N2];
                            if(dd>dist){dist=dd;ind.chromossome[pp].maxI=N1;ind.chromossome[pp].maxJ=N2;}
                        }
                    }
                }
                ind.chromossome[pp].fVk=dist;
            }
            ind.calcFS(tGraph.maxDistance);
            ind.calcGS();
            ind.calcFitness();
            geneticPopulation.populationTIndividual.push_back(ind);
        }
    }
    std::sort(geneticPopulation.populationTIndividual.begin(),
              geneticPopulation.populationTIndividual.end(),
              [](TIndividual& one,TIndividual& two){
                  if(one.rank!=two.rank)return one.rank<two.rank;
                  if(one.crowding!=two.crowding)return one.crowding>two.crowding;
                  return one.fitness<two.fitness;});
    TIndividual tInd=geneticPopulation.populationTIndividual[0];
    int resetCounter=0;
    clock_t tStart=clock();
    for(unsigned gen=0;gen<generations;gen++){
        geneticPopulation=geneticGenerations(geneticPopulation,tGraph);
        if(geneticPopulation.populationTIndividual.empty())break;
        std::sort(geneticPopulation.populationTIndividual.begin(),
                  geneticPopulation.populationTIndividual.end(),
                  [](TIndividual& one,TIndividual& two){
                      if(one.rank!=two.rank)return one.rank<two.rank;
                      if(one.crowding!=two.crowding)return one.crowding>two.crowding;
                      return one.fitness<two.fitness;});
        if(!geneticPopulation.populationTIndividual.empty()&&geneticPopulation.populationTIndividual[0].fitness<tInd.fitness){
            tInd=geneticPopulation.populationTIndividual[0];
            updateTGraphDistrics(tGraph,tInd);
            resetCounter=0;
        } else {
            if(resetLimit>0&&resetCounter>=(int)resetLimit-1){
                geneticPopulation.populationTIndividual.clear();
                std::vector<TIndividual> genNew=geneticPopulation.generateNew(tGraph,numNodes,numDistricts);
                if(genNew.empty()){
                    TIndividual ind(numNodes,numDistricts);
                    for(int node=0;node<numNodes;node++){
                        int d=rand()%numDistricts;
                        ind.addNode(d,node);
                        ind.addDistrictSize(d);
                        ind.addDistrictActivity(d,tGraph.getActivity0(node),tGraph.getActivity1(node));
                    }
                    for(int pp=0;pp<numDistricts;pp++){
                        double dist=0;
                        for(int n1=0;n1<(int)ind.chromossome[pp].nodes.size();n1++){
                            for(int n2=0;n2<(int)ind.chromossome[pp].nodes.size();n2++){
                                int N1=ind.chromossome[pp].nodes[n1];
                                int N2=ind.chromossome[pp].nodes[n2];
                                if(N1>=0&&(unsigned)N1<distances.size()&&N2>=0&&(unsigned)N2<distances[N1].size()){
                                    double dd=distances[N1][N2];
                                    if(dd>dist){dist=dd;ind.chromossome[pp].maxI=N1;ind.chromossome[pp].maxJ=N2;}
                                }
                            }
                        }
                        ind.chromossome[pp].fVk=dist;
                    }
                    ind.calcFS(tGraph.maxDistance);
                    ind.calcGS();
                    ind.calcFitness();
                    genNew.push_back(ind);
                }
                geneticPopulation.populationTIndividual=genNew;
                std::sort(geneticPopulation.populationTIndividual.begin(),
                          geneticPopulation.populationTIndividual.end(),
                          [](TIndividual& one,TIndividual& two){
                              if(one.rank!=two.rank)return one.rank<two.rank;
                              if(one.crowding!=two.crowding)return one.crowding>two.crowding;
                              return one.fitness<two.fitness;});
                if(!geneticPopulation.populationTIndividual.empty()&&populationSize>0)
                    geneticPopulation.populationTIndividual[populationSize-1]=tInd;
                resetCounter=0;
            } else {
                resetCounter++;
            }
        }
    }
    double minF=tInd.functionF;
    double minG=tInd.functionG;
    double minFit=tInd.fitness;
    struct stat st;
    memset(&st,0,sizeof(st));
    if(stat("results",&st)==-1){mkdir("results",0755);}
    std::stringstream cs;
    cs<<"results/"<<file<<"-Best-[,"<<minFit<<",]F[,"<<minF<<",]G[,"<<minG<<",]-Mut[,"<<mutation<<",]Pop[,"<<populationSize<<",]Sel[,"<<selectedPercent<<",]Gen[,"<<generations<<",]Res[,"<<resetLimit<<",]Time[,"<<(double)(clock()-tStart)/CLOCKS_PER_SEC<<",].txt";
    std::string filename=cs.str();
    {
        std::ofstream outfile(filename.c_str());
        if(!outfile.is_open()){
            std::ofstream errfile("results/error_output.txt");
            errfile<<"Could not open output file.\n";
            errfile.close();
            std::ofstream fallback("results/fallback_solution.txt");
            fallback<<"Fallback solution\n1\n0\t0\t0\n-1\n";
            fallback.close();
            return 0;
        }
        if(tInd.numDistricts<=0||tInd.chromossome.empty()){
            outfile<<"No solution found.\n";
        } else {
            outfile<<"F\tG\tH\tPorcent Med.\tPsi\n";
            outfile<<tInd.functionF<<"\t"<<tInd.functionG<<"\t"<<((tInd.functionF+ tInd.functionG)*100000)<<"\t"<<(((double)tInd.getIndividualSize()/numNodes)*100.0)<<"\t"<<tInd.functionG<<"\n";
            for(int p=0;p<tGraph.numDistricts;p++){
                outfile<<p+1;
                for(int n=0;n<(int)tInd.chromossome[p].nodes.size();n++){
                    int node=tInd.chromossome[p].nodes[n];
                    outfile<<"\n"<<node<<"\t";
                    int cx=(int)tGraph.getCoordX(node);
                    int cy=(int)tGraph.getCoordY(node);
                    outfile<<cx<<"\t"<<cy;
                }
                outfile<<"\n-1\n\n";
            }
        }
        outfile.close();
    }
    return 0;
}
