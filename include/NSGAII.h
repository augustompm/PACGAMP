// NSGAII.h
#pragma once
#include "globals.h"
#include "TIndividual.h"
void nonDominatedSort(std::vector<TIndividual> &pop);
void crowdingDistanceAssignment(std::vector<TIndividual> &pop);
