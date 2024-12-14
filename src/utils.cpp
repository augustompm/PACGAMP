// utils.cpp
#include "utils.h"
void skipLines(std::istream& pStream, size_t pLines){std::string s;for(;pLines;--pLines)std::getline(pStream,s);}
void addActivity(double meters,double readingTime){mi[0]+=meters;mi[1]+=readingTime;}
void miCalc(int numDistricts){if(numDistricts>0){mi[0]=mi[0]/numDistricts;mi[1]=mi[1]/numDistricts;}}
void miPrint(){}
