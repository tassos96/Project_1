#include "Assignment.h"

void lloydAssign(const vector<Cluster *> & clusters, int & assignmentsNum) {
    vector<vector<unsigned char> *> centroids;
    for (int i = 0; i < clusters.size(); ++i)
        centroids.push_back(clusters.at(i)->getCentroid());

    vector<Image *> * clustImgs;
    for (int i = 0; i < clusters.size(); ++i) {
        clustImgs = clusters.at(i)->getClusterImgs();
        vector<Image *>::iterator it = clustImgs->begin();
        while(it != clustImgs->end()) {
            int closestClust = closestClusterIdx(*it,&centroids);
            if(closestClust != i) { // reassign image to new cluster
                clusters.at(closestClust)->addImg(*it);
                it = clusters.at(i)->removeImg(it);
                ++assignmentsNum;
            }
            else
                ++it;
        }
    }

}

void lloydAssign(const vector<Cluster *> & clusters, vector<Image *> *imgs) { // first assignment
    vector<vector<unsigned char> *> centroids;
    for (int i = 0; i < clusters.size(); ++i)
        centroids.push_back(clusters.at(i)->getCentroid());

    for (int i = 0; i < imgs->size(); ++i) {
        int closestClust = closestClusterIdx(imgs->at(i),&centroids);
        clusters.at(closestClust)->addImg(imgs->at(i));
    }
}