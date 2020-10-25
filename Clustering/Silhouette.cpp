#include "Silhouette.h"

//Return index of closest neighbour cluster, used for calculation of b(i)
int neighborClusterIdx(Image * img, vector<vector<unsigned char> *> *centroids, int imgClusterIdx) {
    int minDistance = numeric_limits<int>::max();
    int clustIdx;
    for (int i = 0; i < centroids->size(); ++i) {
        if(i == imgClusterIdx)
            continue;
        int newDist = manhattanDistance(img->getPixels(), centroids->at(i));
        if(minDistance > newDist) {
            minDistance = newDist;
            clustIdx = i;
        }
    }
    return clustIdx;
}

//Calculate average distance of image to all data points of a cluster
double avgL1Dist(Image *img, unordered_map<int, Image *> *imgs) {
    double sum = 0;
    bool inClust = false;
    for(const pair<const int, Image*> &i : *imgs){
        if(img->getId() == i.first) {
            inClust = true;
            continue;
        }
        sum += manhattanDistance(i.second->getPixels(), img->getPixels());
    }
    return inClust ? sum/((int)imgs->size()-1) : sum/(int)imgs->size();
}

//Calculate silhouette of an object
double silhouetteObject(Image * img, const vector<Cluster *> & clusters, int imgClusterIdx) {
    vector<vector<unsigned char> *> centroids;
    gatherCentroids(clusters,&centroids);
    int neighorClst = neighborClusterIdx(img ,&centroids, imgClusterIdx);

    double a_i = avgL1Dist(img, clusters.at(imgClusterIdx)->getClusterImgs());

    double b_i = avgL1Dist(img, clusters.at(neighorClst)->getClusterImgs());

    double maxAvgDist = max(a_i, b_i);

    return (b_i - a_i)/maxAvgDist;
}

//Calculate silhouette of a cluster
double silhouetteCluster(const vector<Cluster *> & clusters, int clusterIdx) {
    double sum = 0;
    for(const pair<const int, Image*> &img : *clusters.at(clusterIdx)->getClusterImgs()) {
        sum += silhouetteObject(img.second, clusters, clusterIdx);
    }

    return sum/clusters.at(clusterIdx)->getClusterImgs()->size();
}

//Calculate all silhouettes [s1,...,si,...,sΚ, stotal]
vector<double> silhouette(const vector<Cluster *> & clusters) {
    double sum = 0;
    vector<double> toRet;
    toRet.reserve(clusters.size()+1);
    for(int i = 0; i < clusters.size(); ++i) {
        double s_i = silhouetteCluster(clusters, i);
        toRet.push_back(s_i);
        sum += s_i;
    }
    double sTotal = sum/clusters.size();
    toRet.push_back(sTotal);
    return toRet;
}