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
    unordered_map<int, char> coinFlips;
public:
    F(int,double,int);

    char flipTheCoin(vector<unsigned char> *);

};

class HyperCube {
private:
    vector<F *> projectors;
    int cubeDimension;
    unordered_map<string, Bucket *> vertices;

    void splitIntoVertices(int, vector<Image *> *);
public:
    HyperCube(int, double, int, int, int, vector<Image *> *);
    virtual ~HyperCube();
    string getVertexIdx(Image *);
    Bucket * getVertexByImg(Image *);
    Bucket * getVertexByIdx(const string &);
};


#endif //PROJECT_TASK1_HYPERCUBE_H
