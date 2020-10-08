//
// Created by sysgod on 08/10/2020.
//

#include "hashFuncs.h"

SimpleHash::SimpleHash(int dim, double w, int nBuckts) {
    this->dimension = dim;
    this->gridW = w;
    this->numBuckets = nBuckts;
    this->shifts = new vector<double>();
    this->randShifts();
}


SimpleHash::~SimpleHash() {
    delete this->shifts;
}


void SimpleHash::randShifts() {
    for (int i = 0; i < this->dimension; ++i) {
        this->shifts->push_back(generateDcml());
    }
}

void SimpleHash::outShifts() {
    vector<double>::iterator it;
    int s = 0;
    for (it = shifts->begin(); it < shifts->end() ; ++it) {
        cout << "S" << s++ << " : " << *it << endl;
    }
}

double SimpleHash::generateDcml() {
    double num = (double)rand() / RAND_MAX;
    return this->gridW*num;
}

int SimpleHash::mod(int divident,int divisor) {
    if(divident >= 0) {
        return divident % divisor;
    }
    return divident % divisor + divisor;
}

int SimpleHash::modularExp(int base, unsigned int exp, int div) {
    vector<unsigned int> results;
    unsigned int prevRes;
    for (unsigned int i = 1; i < exp; i*=2) {
        unsigned int nextRes;
        if(i == 1)
            nextRes = SimpleHash::mod(base,div);
        else
            nextRes = SimpleHash::mod(pow(prevRes,2),div);

        if((i & exp) != 0)
            results.push_back(nextRes);

        prevRes = nextRes;
    }

    vector<unsigned int>::iterator it;
    int factor = 1;
    for (it = results.begin(); it < results.end() ; ++it) {
        factor *= *it;
    }
    return SimpleHash::mod(factor,div);
}