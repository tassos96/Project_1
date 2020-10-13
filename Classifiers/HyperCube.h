

#ifndef PROJECT_TASK1_HYPERCUBE_H
#define PROJECT_TASK1_HYPERCUBE_H

#include <unordered_map>
#include "../Common/bucket.h"
#include "../Common/hashFuncs.h"
#include "../Common/Distance.h"

using namespace std;

class F {
private:
    SimpleHash h;
    unordered_map<int,unsigned char> diceRolls;
public:
    F(int,double,int);

    unsigned char rollTheDice(vector<unsigned char> *);

};

class HyperCube {
private:
    vector<F *> projectors;
    int cubeDimension;
    unordered_map<string, Bucket *> vertices;
public:
    HyperCube(int, double, int, int);
    virtual ~HyperCube();
    void splitIntoVertices(int, unordered_map<int, Image *> *);
    string getVerticeIdx(Image * img);
    Bucket * getVertice(Image * img);
};


#endif //PROJECT_TASK1_HYPERCUBE_H
