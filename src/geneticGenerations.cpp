// geneticGenerations.cpp
#include "geneticGenerations.h"
#include <algorithm>

TIndividual geneticCrossover(TGraph tGraph,TIndividual A,TIndividual B){
    TIndividual C(tGraph.numNodes,tGraph.numDistricts);
    if(tGraph.numNodes<=0)return C;
    int cut=rand()%tGraph.numNodes;
    for(int p=0;p<tGraph.numDistricts;p++){
        for(int n=0;n<(int)A.chromossome[p].nodes.size();n++){
            if(C.getIndividualSize()<cut){
                int node=A.chromossome[p].nodes[n];
                if(!C.checkAssignedNode(node))C.addNode(p,node),C.addDistrictActivity(p,tGraph.getActivity0(node),tGraph.getActivity1(node));
            }
        }
    }
    for(int p=0;p<tGraph.numDistricts;p++){
        for(int n=0;n<(int)B.chromossome[p].nodes.size();n++){
            int node=B.chromossome[p].nodes[n];
            if(!C.checkAssignedNode(node))C.addNode(p,node),C.addDistrictActivity(p,tGraph.getActivity0(node),tGraph.getActivity1(node));
        }
    }
    for(int p=0;p<tGraph.numDistricts;p++){
        double dist=0;
        for(int n1=0;n1<(int)C.chromossome[p].nodes.size();n1++){
            for(int n2=0;n2<(int)C.chromossome[p].nodes.size();n2++){
                int N1=C.chromossome[p].nodes[n1];int N2=C.chromossome[p].nodes[n2];
                if(N1>=0&&(unsigned)N1<distances.size()&&N2>=0&&(unsigned)N2<distances[N1].size()){
                    double d=distances[N1][N2];
                    if(d>dist){dist=d;C.chromossome[p].maxI=N1;C.chromossome[p].maxJ=N2;}
                }
            }
        }
        C.chromossome[p].fVk=dist;
    }
    C.calcFS(tGraph.maxDistance);
    C.calcGS();
    C.calcFitness();
    return C;
}

void geneticMutation(TGraph &tGraph,TIndividual &t){
    for(int p=0;p<tGraph.numDistricts;p++){
        for(int i=0;i<(int)t.chromossome[p].nodes.size();i++){
            if(populationSize>0&&rand()%100<(int)mutation){
                int node=t.chromossome[p].nodes[i];
                CheckRemoval check(tGraph,t.chromossome[p].nodes,p,i,node);
                if(check.checkRemoval()){
                    t.removeDistrictActivity(p,tGraph.getActivity0(node),tGraph.getActivity1(node));
                    t.reduceDistrictSize(p);
                    t.reduceIndividualSize();
                    t.chromossome[p].nodes.erase(t.chromossome[p].nodes.begin()+i);
                    tGraph.setDistrict(node,-1);
                    if(tGraph.numDistricts>0){
                        int newp=rand()%tGraph.numDistricts;
                        t.addNode(newp,node);
                        t.addDistrictActivity(newp,tGraph.getActivity0(node),tGraph.getActivity1(node));
                        t.addDistrictSize(newp);
                        tGraph.setDistrict(node,newp);
                    }
                }
            }
        }
    }
    for(int p=0;p<tGraph.numDistricts;p++){
        double dist=0;
        for(int n1=0;n1<(int)t.chromossome[p].nodes.size();n1++){
            for(int n2=0;n2<(int)t.chromossome[p].nodes.size();n2++){
                int N1=t.chromossome[p].nodes[n1];int N2=t.chromossome[p].nodes[n2];
                if(N1>=0&&(unsigned)N1<distances.size()&&N2>=0&&(unsigned)N2<distances[N1].size()){
                    double d=distances[N1][N2];
                    if(d>dist){dist=d;t.chromossome[p].maxI=N1;t.chromossome[p].maxJ=N2;}
                }
            }
        }
        t.chromossome[p].fVk=dist;
    }
    t.calcFS(tGraph.maxDistance);
    t.calcGS();
    t.calcFitness();
}

GeneticPopulation geneticGenerations(GeneticPopulation gp,TGraph tGraph){
    std::vector<TIndividual>pop=gp.populationTIndividual;
    if(pop.empty())return gp;
    nonDominatedSort(pop);
    crowdingDistanceAssignment(pop);
    std::vector<TIndividual> selected;selected.reserve((size_t)selectedPopulation);
    for(unsigned i=0;i<selectedPopulation&&i<pop.size();i++){selected.push_back(pop[i]);}
    std::vector<TIndividual>offspring;offspring.reserve((size_t)populationSize);
    for(unsigned i=0;i<selectedPopulation;i+=2){
        if(selected.size()>i&&(selected.size()>i+1||selectedPopulation==1)){
            TIndividual pA=selected[i];
            TIndividual pB=selected[(i+1)%selected.size()];
            TIndividual c=geneticCrossover(tGraph,pA,pB);
            geneticMutation(tGraph,c);
            offspring.push_back(c);
        }
    }
    std::vector<TIndividual> newPop=pop;
    for(auto&o:offspring)newPop.push_back(o);
    if(!newPop.empty()){
        nonDominatedSort(newPop);
        crowdingDistanceAssignment(newPop);
        std::sort(newPop.begin(),newPop.end(),[](TIndividual&a,TIndividual&b){
            if(a.rank!=b.rank)return a.rank<b.rank;
            if(a.crowding!=b.crowding)return a.crowding>b.crowding;
            return a.fitness<b.fitness;
        });
        while((int)newPop.size()>(int)populationSize)newPop.pop_back();
        gp.populationTIndividual=newPop;
    }
    return gp;
}
