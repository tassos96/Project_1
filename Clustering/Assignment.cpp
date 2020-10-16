#include "Assignment.h"

void lloydAssign(const vector<Cluster *> & clusters) {
    vector<vector<unsigned char> *> centroids;
    for (int i = 0; i < clusters.size(); ++i)
        centroids.push_back(clusters.at(i)->getCentroid());

    vector<Image *> * clustImgs;
    vector<tuple<int,int,int>> imgsToMove; // Imgs that need to be deleted from old clusters and moved to new one
    for (int i = 0; i < clusters.size(); ++i) {
        clustImgs = clusters.at(i)->getClusterImgs();
        for (int z = 0; z < clustImgs->size(); ++z) {
            int closestClust = closestClusterIdx(clustImgs->at(z),&centroids);
            if(closestClust != i) { // reassign image to new cluster
                imgsToMove.emplace_back(make_tuple(i,closestClust,z));
            }
        }
    }

    for (int i = 0; i < imgsToMove.size(); ++i) {
        int oldClust = get<0>(imgsToMove.at(i));
        int newClust = get<1>(imgsToMove.at(i));
        int imgIdx = get<2>(imgsToMove.at(i));
        clusters.at(newClust)->addImg(clusters.at(oldClust)->removeImg(imgIdx));
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