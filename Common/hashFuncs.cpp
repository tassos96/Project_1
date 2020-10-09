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

double SimpleHash::generateDcml() const{
    unsigned seed = system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(0.0, this->gridW);
    return distribution(generator);
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
    for (unsigned int i = 1; i <= exp; i*=2) {
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

int SimpleHash::hashResult(vector<unsigned char> *pixels) {
    vector<int> a;
    /* calculate projections */
    for (int i = 0; i < this->dimension; ++i) {
        int a_i = floor(((int)pixels->at(i) - (double)this->shifts->at(i)) / this->gridW);
        a.push_back(a_i);
    }

    /* calculate hash result */
    int sum= 0;
    int m = pow(2,32) - 5;
    for (int i= this->dimension-1; i >= 0; --i) {
        int a_i = a.at(i);
        int factor_1 = SimpleHash::modularExp(m,
                                              this->dimension-1-i,
                                              this->numBuckets);
        int factor_2 = SimpleHash::mod(a_i, this->numBuckets);
        sum+= SimpleHash::mod(factor_1 * factor_2, this->numBuckets);
    }
    return mod(sum, this->numBuckets);
}