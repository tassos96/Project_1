#include "Cluster.h"

vector<Cluster *> * makeClusters(vector<Image *> *centroids, int numClusters) {
    vector<Cluster *> * vec = new vector<Cluster *>;
    vec->reserve(numClusters);
    for (int i = 0; i < numClusters; ++i) {
        Cluster * newClust = new Cluster(centroids->at(i));
        vec->push_back(newClust);
    }
    return vec;
}

Cluster::Cluster(Image * centroidImg) {
    this->centroid = centroidImg->getPixels();
    this->centrIsInDataset = true;
    this->firstCentroidPtr = centroidImg; // keep the Image for the centroid update
    this->imgs_in_cluster = new vector<Image *>;
}


Cluster::~Cluster() {
    delete this->imgs_in_cluster;
    if(!this->centrIsInDataset)
        delete this->centroid;
}


void Cluster::updateCentroid() {
    if(this->centrIsInDataset) { // make sure not to lose the image upon updating centroid
        this->centrIsInDataset = false;
        this->imgs_in_cluster->push_back(this->firstCentroidPtr);
        this->firstCentroidPtr = nullptr;
    } else {
        delete this->centroid;
    }
    this->centroid = getMedian(this->imgs_in_cluster,this->centroid->size());
}

vector<Image *> * Cluster::getClusterImgs() {
    return this->imgs_in_cluster;
}

vector<unsigned char> * Cluster::getCentroid() {
    return this->centroid;
}

Image * Cluster::removeImg(int idx) {
    Image * toRet =this->imgs_in_cluster->at(idx);
    this->imgs_in_cluster->erase(this->imgs_in_cluster->begin() + idx);
    return toRet;
}

void Cluster::addImg(Image * newImg) {
    this->imgs_in_cluster->push_back(newImg);
}
