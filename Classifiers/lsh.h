#ifndef PROJECT_TASK1_LSH_H
#define PROJECT_TASK1_LSH_H

#include <vector>
#include "../Common/image.h"
#include "../Common/hashFuncs.h"
#include "../Common/bucket.h"

using namespace std;

class LshTable {
private:
    int tableSize;
    AmplifiedHash gHash;
    vector<Bucket *> *table;
    void splitIntoBuckets(int, vector<Image *> *);
public:
    LshTable(int, vector<Image *> *, int, double, int );
    virtual ~LshTable();
};

class Lsh {
private:
    int numTables;
    vector<LshTable *> *tables;
    void buildTables(int, vector<Image *> *, int, double, int);
public:
    Lsh(int,int, vector<Image *> *, int, double, int);
    virtual ~Lsh();
};

#endif //PROJECT_TASK1_LSH_H
