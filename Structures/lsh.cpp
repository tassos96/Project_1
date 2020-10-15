#include "lsh.h"

#define TABLE_SIZE_DIV 16

LshTable::LshTable(int imgNum,
                   vector<Image *> *imgs,
                   int dim,
                   double w,
                   int numHashes): gHash(dim,
                                         w,
                                         imgNum / TABLE_SIZE_DIV,
                                         numHashes){
    this->tableSize = imgNum / TABLE_SIZE_DIV;
    this->table = new unordered_map<int,Bucket *>;
    this->splitIntoBuckets(imgNum, imgs);
}

LshTable::~LshTable() {
    for (int i = 0; i < tableSize; ++i) {
        try { // in case not all buckets were used
            delete this->table->at(i);
        }
        catch (out_of_range &) {
            continue;
        }
    }
    delete this->table;
}

tuple<int, Bucket* > LshTable::getBucket(Image* image) {
    int index = this->gHash.hashResult(image);
    try {
        return make_tuple(index, this->table->at(index));
    }
    catch (out_of_range &) {
        //in case bucket is empty return nullptr
        return make_tuple(index, nullptr);
    }
}


void LshTable::splitIntoBuckets(int imgNum, vector<Image *> * imgs) {
    for (int i = 0; i < imgNum; ++i) {
        Image * imgPtr = imgs->at(i);
        int index = this->gHash.hashResult(imgPtr);
//        cout << "Placing  image #" << i << " at bucket #" << index << endl;
        try {
            this->table->at(index)->insertImage(imgPtr);
        }
        catch (out_of_range &) {
            pair<int, Bucket *> newPair(index, new Bucket());
            this->table->insert(newPair);
            this->table->at(index)->insertImage(imgPtr);
        }
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

LshTable* Lsh::getHashTable(int index) {
    return this->tables->at(index);
}

int Lsh::getNumTables(){
    return this->numTables;
}
