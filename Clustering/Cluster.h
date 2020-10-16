#ifndef PROJECT_TASK1_CLUSTER_H
#define PROJECT_TASK1_CLUSTER_H

#include "../Common/image.h"
#include "UtilsCluster.h"

class Cluster {
private:
    vector<unsigned char> *centroid;
    Image * firstCentroidPtr;
    bool centrIsInDataset;
    vector<Image *> * imgs_in_cluster;
public:
    Cluster(Image *);
    ~Cluster();
    void updateCentroid();
    vector<Image *> * getClusterImgs();
    vector<unsigned char> * getCentroid();
    vector<Image *>::iterator removeImg(vector<Image *>::iterator);
    void addImg(Image *);
};

vector<Cluster *> * makeClusters(vector<Image *> *centroids, int numClusters);

#endif //PROJECT_TASK1_CLUSTER_H
