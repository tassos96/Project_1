#include "Assignment.h"


void lloydAssign(const vector<Cluster *> & clusters, vector<Image *> *imgs) { // first assignment
    vector<vector<unsigned char> *> centroids;
    gatherCentroids(clusters,&centroids);

    for (int i = 0; i < imgs->size(); ++i) {
        int closestClust = closestClusterIdx(imgs->at(i),&centroids);
        clusters.at(closestClust)->addImg(imgs->at(i));
    }
}

void lloydAssign(const vector<Cluster *> & clusters, int & assignmentsNum) {
    vector<vector<unsigned char> *> centroids;
    gatherCentroids(clusters,&centroids);


    unordered_map<int,Image *> * clustImgs;
    for (int i = 0; i < clusters.size(); ++i) {
        clustImgs = clusters.at(i)->getClusterImgs();
        unordered_map<int,Image *>::iterator it = clustImgs->begin();
        while(it != clustImgs->end()) {
            int closestClust = closestClusterIdx(it->second,&centroids);
            if(closestClust != i) { // reassign image to new cluster
                clusters.at(closestClust)->addImg(it->second);
                it = clusters.at(i)->removeImg(it);
                ++assignmentsNum;
            }
            else
                ++it;
        }
    }
}

using searchResults = vector<tuple<int,Image*>>;

int nextIt(vector<searchResults::iterator> *iterators, vector<searchResults> * results) {
    int minDistance = numeric_limits<int>::max();
    int nextIt = -1;
    for(int i = 0; i < iterators->size(); ++i) {
        if(iterators->at(i) == results->at(i).end())
            continue;
        if(get<0>(*iterators->at(i)) < minDistance) {
            minDistance =  get<0>(*iterators->at(i));
            nextIt = i;
        }
    }
    return nextIt;
}

int processResults(vector<searchResults> * results, const vector<Cluster *> & clusters) {
    vector<searchResults::iterator> iterators;
    iterators.reserve(results->size()); // iterators will point to the first <distance,Image> pair for each range search
    for (int i = 0; i < results->size(); ++i) {
        iterators.push_back(results->at(i).begin());
    }
    int newAssignments = 0;
    int itIdx = nextIt(&iterators, results);
    while(itIdx != -1) {
        Image * imgPtr = get<1>(*iterators.at(itIdx));
        if(imgIsCentroid(clusters, imgPtr) || imgPtr->isAssignedToClst()) {
            ++iterators.at(itIdx);
            itIdx = nextIt(&iterators, results);
            continue;
        }
        int closestClust = itIdx;
        int currClust = getImgCluster(clusters, imgPtr);
        if(closestClust != currClust) {
            clusters.at(closestClust)->addImg(imgPtr);
            if(currClust != -1) {
                clusters.at(currClust)->removeImg(imgPtr->getId());
            }
            ++newAssignments;
        }
        imgPtr->assignImageToClst();
        ++iterators.at(itIdx);
        itIdx = nextIt(&iterators, results);
    }
    return newAssignments;
}

void reverseAssign(const vector<Cluster *> & clusters,
                   vector<Image *> *allImgs,
                   Lsh* lsh,
                   int & totalChanges,
                   HyperCube* hpcb,
                   int checkThrshld,
                   int maxProbes,
                   int srchThresh,
                   int clustThresh) {
    vector<vector<unsigned char> *> centroids;
    gatherCentroids(clusters,&centroids);
    int radius = minCentroidDist(&centroids);
    while(true) {
        vector<searchResults> results;
        for (int i = 0; i < centroids.size(); ++i) {
            if(hpcb == nullptr)
                results.push_back(aproxRangeSrch(centroids.at(i),lsh,radius,srchThresh));
            else
                results.push_back(aproxRangeSrch(centroids.at(i),hpcb,checkThrshld,maxProbes,radius));

            unmarkImgs(allImgs, allImgs->size());
        }
        int changes = processResults(&results, clusters);
        totalChanges += changes;
        if(changes == clustThresh)
            break;
        radius*=2;
    }

    for (int i = 0; i < allImgs->size(); ++i) {
        Image *imgPtr = allImgs->at(i);
        if (imgPtr->isAssignedToClst())
            continue;

        int closestClust = closestClusterIdx(imgPtr, &centroids);
        int currClust = getImgCluster(clusters, imgPtr);
        if (closestClust != currClust) {
            clusters.at(closestClust)->addImg(imgPtr);
            ++totalChanges;
            if (currClust != -1) {
                clusters.at(currClust)->removeImg(imgPtr->getId());
            }
        }
    }

    unassignImgs(allImgs, allImgs->size());
}

