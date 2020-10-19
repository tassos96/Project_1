#ifndef PROJECT_TASK1_CLUSTER_H
#define PROJECT_TASK1_CLUSTER_H

#include <fstream>

#include "../Common/image.h"
#include "UtilsCluster.h"

class Cluster {
private:
    vector<unsigned char> *centroid;
    Image * firstCentroidPtr;
    bool centrIsInDataset;
    unordered_map<int,Image *> * imgs_in_cluster;
public:
    Cluster(Image *);
    ~Cluster();
    void updateCentroid();
    unordered_map<int,Image *> * getClusterImgs();
    vector<unsigned char> * getCentroid();
    unordered_map<int,Image *>::iterator removeImg(unordered_map<int,Image *>::iterator);
    void removeImg(const int & key);
    void addImg(Image *);
    bool centroidIsImg() const;
    int getCentrId() const;
};

vector<Cluster *> * makeClusters(vector<Image *> *centroids, int numClusters);
void gatherCentroids(const vector<Cluster *> & clusters, vector<vector<unsigned char> *> *vec);
int getImgCluster(const vector<Cluster *> & clusters, Image * img);
bool imgIsCentroid(const vector<Cluster *> & clusters, Image * img);

void printClstrRslts(string &outFilename, string &method, vector<Cluster *> * clusters,
                     string &dur, vector<double> *silhouetteRes,
                     bool complete);

#endif //PROJECT_TASK1_CLUSTER_H
