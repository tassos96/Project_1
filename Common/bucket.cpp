#include "bucket.h"

Bucket::Bucket() {
    this->images = new vector<Image *>;
    this->g_hash_results = new vector<unsigned int>;
}

Bucket::~Bucket() {
    delete this->images;
    delete this->g_hash_results;
}

void Bucket::insertImage(Image * img) {
    this->images->push_back(img);
}

vector<Image *> *Bucket::getImages() {
    return this->images;
}

void Bucket::insertHashRes(unsigned int res) {
    this->g_hash_results->push_back(res);
}

vector<unsigned int> *Bucket::getHashReslts() {
    return this->g_hash_results;
}