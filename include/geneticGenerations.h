// geneticGenerations.h
#pragma once
#include "globals.h"
#include "TGraph.h"
#include "TIndividual.h"
#include "GeneticPopulation.h"
#include "geneticOps.h"
#include "NSGAII.h"
TIndividual geneticCrossover(TGraph tGraph,TIndividual parentA,TIndividual parentB);
void geneticMutation(TGraph &tGraph,TIndividual &tIndividual);
GeneticPopulation geneticGenerations(GeneticPopulation geneticPopulation,TGraph tGraph);
