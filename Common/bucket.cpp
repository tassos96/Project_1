#include "bucket.h"

Bucket::Bucket() {
    this->images = new vector<Image *>;
}

Bucket::~Bucket() {
    delete this->images;
}

void Bucket::insertImage(Image * img) {
    this->images->push_back(img);
}

vector<Image *> *Bucket::getImages() {
    return this->images;
}