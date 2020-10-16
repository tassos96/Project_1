#include "algorithm.h"

vector<Cluster *> *clustering(string assignMethod, vector<Image *> imgs, int numClusters) {
    int imgNum = imgs.size();
    vector<Image *> centroids = kMeansPPlus(&imgs, numClusters); // choose initial centroids
    vector<Cluster *> * clusters = makeClusters(&centroids, numClusters ); // create clusters
    if(assignMethod == "lloyd")
        lloydAssign(*clusters, &imgs); // initial assignment of images to clusters
    int iterations = 0;
    while (iterations < imgNum) {
        for (Cluster * clst: *clusters) {
            clst->updateCentroid();
        }
        int assignmentsPerformed = 0;
        if(assignMethod == "lloyd") {
            lloydAssign(*clusters, assignmentsPerformed);
        }
        if(assignmentsPerformed == 0){ // convergence witnessed
            cout << "converged" << endl;
            break;
        }

        ++iterations;
    }

    return clusters;
}