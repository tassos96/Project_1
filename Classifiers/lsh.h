#ifndef PROJECT_TASK1_LSH_H
#define PROJECT_TASK1_LSH_H

#include <vector>
#include <unordered_map>
#include "../Common/image.h"
#include "../Common/hashFuncs.h"
#include "../Common/bucket.h"

using namespace std;

class LshTable {
private:
    int tableSize;
    AmplifiedHash gHash;
    unordered_map<int, Bucket *> *table;
    void splitIntoBuckets(int, unordered_map<int, Image *> *);
public:
    LshTable(int, unordered_map<int, Image *> *, int, double, int );
    virtual ~LshTable();
};

class Lsh {
private:
    int numTables;
    vector<LshTable *> *tables;
    void buildTables(int, unordered_map<int, Image *> *, int, double, int);
public:
    Lsh(int,int, unordered_map<int, Image *> *, int, double, int);
    virtual ~Lsh();
};

#endif //PROJECT_TASK1_LSH_H
