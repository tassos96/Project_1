//
// Created by sysgod on 08/10/2020.
//

#ifndef PROJECT_TASK1_HASHFUNCS_H
#define PROJECT_TASK1_HASHFUNCS_H

#include "image.h"
#include <cmath>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

class SimpleHash {
private:
    int dimension;
    double gridW;
    int tableSize; // the hash table size
    vector<double> *shifts;
    void randShifts();
    static int mod(int,int);
    static int modularExp(unsigned int,unsigned int,int);
public:
    SimpleHash(int,double,int);
    ~SimpleHash();
    void outShifts();
    double generateDcml() const;
    int hashResult(vector<unsigned char>*);
    static int mod(unsigned int,int);
};

class AmplifiedHash {
private:
    int tableSize;
    int numHashes; // # of h_i functions
    vector<SimpleHash *> *subhashes;

public:
    AmplifiedHash(int, double, int, int);
    virtual ~AmplifiedHash();
    int hashResult(Image *);
};

#endif //PROJECT_TASK1_HASHFUNCS_H
