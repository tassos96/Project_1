#include "lsh.h"

//#define TABLE_SIZE_DIV 16

LshTable::LshTable(int imgNum,
                   unordered_map<int, Image *> *imgs,
                   int dim,
                   double w,
                   int numHashes): gHash(dim,
                                         w,
                                         pow(2,32/numHashes),
//                                         imgNum / TABLE_SIZE_DIV,
                                         numHashes){
//    this->tableSize = imgNum / TABLE_SIZE_DIV;
    this->tableSize = pow(2,32/numHashes);
    this->table = new unordered_map<int,Bucket *>;
    this->splitIntoBuckets(imgNum, imgs);
}

LshTable::~LshTable() {
    for (int i = 0; i < tableSize; ++i) {
        try { // in case not all buckets were used
            delete this->table->at(i);
        }
        catch (out_of_range & ex) {
            continue;
        }
    }
    delete this->table;
}

void LshTable::splitIntoBuckets(int imgNum, unordered_map<int, Image *> * imgs) {
    for (int i = 0; i < imgNum; ++i) {
        Image * imgPtr = imgs->at(i);
        int index = this->gHash.hashResult(imgPtr);
        try {
            this->table->at(index)->insertImage(imgPtr);
        }
        catch (out_of_range & ex) {
            pair<int, Bucket *> newPair(index, new Bucket());
            this->table->insert(newPair);
            this->table->at(index)->insertImage(imgPtr);
        }
        if((i+1)%5000 == 0)
            cout << "prnt" << endl;
    }
}

Lsh::Lsh(int numTables,
         int imgNum,
         unordered_map<int, Image *> *imgs,
         int dim,
         double w,
         int numHashes){
    this->numTables = numTables;
    this->tables = new vector<LshTable *>;
    this->buildTables(imgNum, imgs, dim, w, numHashes);
}

Lsh::~Lsh() {
    vector<LshTable *>::iterator it;
    for (it=this->tables->begin(); it<this->tables->end(); ++it) {
        delete *it;
    }
    delete this->tables;
}

void Lsh::buildTables(int imgNum,
                      unordered_map<int, Image *> *imgs,
                      int dim,
                      double w,
                      int numHashes) {
    for (int i = 0; i < this->numTables; ++i) {
        this->tables->push_back(new LshTable(imgNum,imgs,dim,w,numHashes));
    }
}