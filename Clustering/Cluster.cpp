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

void gatherCentroids(const vector<Cluster *> & clusters, vector<vector<unsigned char> *> *vec) {
    for (int i = 0; i < clusters.size(); ++i)
        vec->push_back(clusters.at(i)->getCentroid());
}

int getImgCluster(const vector<Cluster *> & clusters, Image * img) {
    int toRet = -1;
    for (int i = 0; i < clusters.size(); ++i) {
        if(clusters.at(i)->getClusterImgs()->end() != clusters.at(i)->getClusterImgs()->find(img->getId())) {
            toRet = i;
            break;
        }
    }
    return toRet;
}

bool imgIsCentroid(const vector<Cluster *> & clusters, Image * img) {
    bool toRet = false;
    for (int i = 0; i < clusters.size(); ++i) {
        if(clusters.at(i)->centroidIsImg() && clusters.at(i)->getCentrId() == img->getId()) {
            toRet = true;
            break;
        }
    }
    return toRet;
}

Cluster::Cluster(Image * centroidImg) {
    this->centroid = centroidImg->getPixels();
    this->centrIsInDataset = true;
    this->firstCentroidPtr = centroidImg; // keep the Image for the centroid update
    this->imgs_in_cluster = new unordered_map<int,Image *>;
}


Cluster::~Cluster() {
    delete this->imgs_in_cluster;
    if(!this->centrIsInDataset)
        delete this->centroid;
}


void Cluster::updateCentroid() {
    int dimension = this->centroid->size();
    if(this->centrIsInDataset) { // make sure not to lose the image upon updating centroid
        this->centrIsInDataset = false;
        this->imgs_in_cluster->insert(make_pair(this->firstCentroidPtr->getId(),this->firstCentroidPtr));
        this->firstCentroidPtr = nullptr;
    } else {
        delete this->centroid;
    }
    this->centroid = getMedian(this->imgs_in_cluster,dimension);
}

unordered_map<int,Image *> * Cluster::getClusterImgs() {
    return this->imgs_in_cluster;
}

bool Cluster::centroidIsImg() const {
    return this->centrIsInDataset;
}

int Cluster::getCentrId() const {
    return this->firstCentroidPtr->getId();
}

vector<unsigned char> * Cluster::getCentroid() {
    return this->centroid;
}

unordered_map<int,Image *>::iterator Cluster::removeImg(unordered_map<int,Image *>::iterator it) {
    return this->imgs_in_cluster->erase(it);
}

void Cluster::removeImg(const int & key) {
    this->imgs_in_cluster->erase(key);
}

void Cluster::addImg(Image * newImg) {
    this->imgs_in_cluster->insert(make_pair(newImg->getId(),newImg));
}
