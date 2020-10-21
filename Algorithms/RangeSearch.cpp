#include "RangeSearch.h"

vector<tuple<int,Image*>> aproxRangeSrch(vector<unsigned char> * queryImage,
                                        Lsh* structure,
                                        double radius,
                                        int threshold) {
    PriorityQueue<PriorityCloser> queue;

    // number of lsh tables
    int numTables = structure->getNumTables();

    int checked = 0;
    for (int i = 0; i < numTables; ++i) {
        LshTable *tbl = structure->getHashTable(i);
        tuple<unsigned int, Bucket *> bucketTpl = tbl->getBucket(queryImage);
        Bucket *buckPtr = get<1>(bucketTpl);
        unsigned int hashRes = get<0>(bucketTpl);
        if (buckPtr == nullptr)
            continue;
        vector<Image *> *buckImgs = buckPtr->getImages();
        vector<unsigned int> *g_hash_results = buckPtr->getHashReslts();
        for (int j = 0; j < buckImgs->size(); ++j) {
            if(buckImgs->at(j)->isMarked())
                continue;
            buckImgs->at(j)->markImage();
            if(g_hash_results->at(j) != hashRes) // images have different hash values before mod
                continue;
            int newDist = manhattanDistance(queryImage, buckImgs->at(j)->getPixels());
            if(newDist <= radius)
                queue.insert(buckImgs->at(j), newDist);

            if(++checked == (2*threshold*numTables))
                break;
        }
        if(checked == (2*threshold*numTables))
            break;
    }

    //gather results
    vector<tuple<int, Image*>> result;
    queue.transferToVector(&result);
    return result;
}

vector<tuple<int, Image*>> aproxRangeSrch(vector<unsigned char> * queryImage,
                                          HyperCube* structure,
                                          int checkThrshld,
                                          int maxProbes,
                                          double radius) {
    PriorityQueue<PriorityCloser> queue;

    vector<string> verticesToCheck;
    string queryVrtx = structure->getVertexIdx(queryImage);
    getVerticesToCheck(verticesToCheck, queryVrtx, queryVrtx.length());

    int checked = 0;    // stop when a lot of potential NNeighbours are checked
    for(int i = 0; i < maxProbes; ++i) {   //start probing vertices
        if(i >= verticesToCheck.size()) // no vertices left to check
            break;
        string curVrtx = verticesToCheck.at(i);
        Bucket * bucketPtr = structure->getVertexByIdx(curVrtx);
        if(bucketPtr == nullptr)
            continue;
        vector<Image *> *buckImgs = bucketPtr->getImages();
        for(int j = 0; j < buckImgs->size(); ++j) {
            int newDist = manhattanDistance(queryImage, buckImgs->at(j)->getPixels());
            if(newDist <= radius)
                queue.insert(buckImgs->at(j), newDist);

            if(++checked == checkThrshld)
                break;
        }
        if(checked == checkThrshld)
            break;
    }

    //gather results
    vector<tuple<int, Image*>> result;
    queue.transferToVector(&result);
    return result;
}
