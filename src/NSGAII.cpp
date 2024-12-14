// NSGAII.cpp
#include "NSGAII.h"
#include <algorithm>
void nonDominatedSort(std::vector<TIndividual> &pop){
    int N=(int)pop.size();
    if(N==0)return;
    std::vector<int>n(N,0);
    std::vector<std::vector<int>>S(N);
    for(int p=0;p<N;p++){
        for(int q=0;q<N;q++){
            bool pd=(pop[p].functionF<=pop[q].functionF&&pop[p].functionG<=pop[q].functionG&&(pop[p].functionF<pop[q].functionF||pop[p].functionG<pop[q].functionG));
            bool qd=(pop[q].functionF<=pop[p].functionF&&pop[q].functionG<=pop[p].functionG&&(pop[q].functionF<pop[p].functionF||pop[q].functionG<pop[p].functionG));
            if(pd&&!qd)S[p].push_back(q);
            else if(qd&&!pd)n[p]++;
        }
    }
    std::vector<std::vector<int>> fronts;
    std::vector<int> current;
    for(int i=0;i<N;i++){if(n[i]==0){pop[i].rank=0;current.push_back(i);}}
    fronts.push_back(current);
    int i=0;
    while(i<(int)fronts.size() && !fronts[i].empty()){
        std::vector<int>next;
        for(auto p:fronts[i]){
            for(auto q:S[p]){
                n[q]--;
                if(n[q]==0){pop[q].rank=i+1;next.push_back(q);}
            }
        }
        if(!next.empty())fronts.push_back(next);
        i++;
    }
}

void crowdingDistanceAssignment(std::vector<TIndividual> &pop){
    int N=(int)pop.size();
    if(N==0)return;
    for(int i=0;i<N;i++)pop[i].crowding=0;
    std::vector<int> idx(N);for(int i=0;i<N;i++)idx[i]=i;
    std::sort(idx.begin(),idx.end(),[&](int a,int b){return pop[a].functionF<pop[b].functionF;});
    if(N>2){pop[idx[0]].crowding=1e9;pop[idx[N-1]].crowding=1e9;for(int k=1;k<N-1;k++){double diff=pop[idx[k+1]].functionF - pop[idx[k-1]].functionF;pop[idx[k]].crowding+=diff;}}
    else{for(int k=0;k<N;k++)pop[idx[k]].crowding=1e9;}
    std::sort(idx.begin(),idx.end(),[&](int a,int b){return pop[a].functionG<pop[b].functionG;});
    if(N>2){pop[idx[0]].crowding=1e9;pop[idx[N-1]].crowding=1e9;for(int k=1;k<N-1;k++){double diff=pop[idx[k+1]].functionG - pop[idx[k-1]].functionG;pop[idx[k]].crowding+=diff;}}
    else{for(int k=0;k<N;k++)pop[idx[k]].crowding=1e9;}
}
