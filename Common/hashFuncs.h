//
// Created by sysgod on 08/10/2020.
//

#ifndef PROJECT_TASK1_HASHFUNCS_H
#define PROJECT_TASK1_HASHFUNCS_H

#include <cstdlib>
#include "image.h"
#include <cmath>

using namespace std;

class SimpleHash {
private:
    int dimension;
    double gridW;
    int numBuckets;
    vector<double> *shifts;

public:
    SimpleHash(int,double,int);
    ~SimpleHash();
    void randShifts();
    void outShifts();
    double generateDcml();
    static int mod(int,int);
    static int modularExp(int,unsigned int,int);
};

class AmplifiedHash {

};

#endif //PROJECT_TASK1_HASHFUNCS_H
