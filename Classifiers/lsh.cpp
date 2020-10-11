#include "lsh.h"

//#define TABLE_SIZE_DIV 16

LshTable::LshTable(int imgNum,
                   vector<Image *> *imgs,
                   int dim,
                   double w,
                   int numHashes): gHash(dim,
                                         w,
                                         pow(2,32/numHashes),
//                                         imgNum / TABLE_SIZE_DIV,
                                         numHashes){
//    this->tableSize = imgNum / TABLE_SIZE_DIV;
    this->tableSize = pow(2,32/numHashes);
    this->table = new vector<Bucket *>;
    this->table->insert(this->table->begin(),this->tableSize, nullptr);
    this->splitIntoBuckets(imgNum, imgs);
}

LshTable::~LshTable() {
    vector<Bucket *>::iterator it;
    for (it=this->table->begin(); it<this->table->end(); ++it) {
        delete *it;
    }
    delete this->table;
}

void LshTable::splitIntoBuckets(int imgNum, vector<Image *> * imgs) {
    for (int i = 0; i < imgNum; ++i) {
        int index = this->gHash.hashResult(imgs->at(i));
        if(this->table->at(index) == nullptr)
            this->table->at(index) = new Bucket();
        this->table->at(index)->insertImage(imgs->at(i));
    }
}

Lsh::Lsh(int numTables,
         int imgNum,
         vector<Image *> *imgs,
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
                      vector<Image *> *imgs,
                      int dim,
                      double w,
                      int numHashes) {
    for (int i = 0; i < this->numTables; ++i) {
        this->tables->push_back(new LshTable(imgNum,imgs,dim,w,numHashes));
    }
}