#include "AproxNN.h"

tuple<vector<tuple<int,Image*>>, microseconds> aproxKNN(Image* queryImage,
                                                        Lsh* structure,
                                                        int numNeighbors,
                                                        int threshold) {
    PriorityQueue<PriorityFurther> queue;

    //start timer
    high_resolution_clock::time_point startTimer = high_resolution_clock::now();

    int numTables = structure->getNumTables();     // number of lsh tables
    int checked = 0; // stop when a lot of potential NNeighbours are checked
    for (int i = 0; i < numTables; ++i) {
        LshTable *tbl = structure->getHashTable(i);
        tuple<unsigned int, Bucket *>bucketTpl = tbl->getBucket(queryImage->getPixels());
        Bucket * buckPtr = get<1>(bucketTpl);
        unsigned int hashRes = get<0>(bucketTpl);
        if(buckPtr == nullptr)
            continue;
        vector<Image *> *buckImgs = buckPtr->getImages();
        vector<unsigned int> *g_hash_results = buckPtr->getHashReslts();
        for (int j = 0; j < buckImgs->size(); ++j) {
            // images have different hash values before mod or the image has been checked in a previous LSH table
            if(buckImgs->at(j)->isMarked() || g_hash_results->at(j) != hashRes)
                continue;
            buckImgs->at(j)->markImage();
            queue.tryInsert(queryImage,buckImgs->at(j),numNeighbors);
            if(++checked == (threshold*numTables))
                break;
        }
        if(checked == (threshold*numTables))
            break;
    }
    //stop timer
    high_resolution_clock::time_point stopTimer = high_resolution_clock::now();
    auto timerDuration = duration_cast<microseconds>(stopTimer - startTimer);

    //gather results
    vector<tuple<int, Image*>> result;
    queue.transferToVector(&result);
    return make_tuple(result, timerDuration);
}

tuple<vector<tuple<int,Image*>>, microseconds> aproxKNN(Image* queryImage,
                                                        HyperCube* structure,
                                                        int checkThrshld,
                                                        int maxProbes,
                                                        int numNeighbors) {
    PriorityQueue<PriorityFurther> queue;

    //start timer
    high_resolution_clock::time_point startTimer = high_resolution_clock::now();

    vector<string> verticesToCheck;
    string queryVrtx = structure->getVertexIdx(queryImage->getPixels());
    getVerticesToCheck(verticesToCheck, queryVrtx, queryVrtx.length());

    int checked = 0;    // stop when a lot of potential NNeighbours are checked
    for(int i = 0; i < maxProbes; ++i) {   // start probing vertices
        if(i >= verticesToCheck.size()) // no vertices left
            break;
        string curVrtx = verticesToCheck.at(i);
        Bucket * bucketPtr = structure->getVertexByIdx(curVrtx);
        if(bucketPtr == nullptr)
            continue;
        vector<Image *> *buckImgs = bucketPtr->getImages();
        for(int j = 0; j < buckImgs->size(); ++j) {
            queue.tryInsert(queryImage, buckImgs->at(j), numNeighbors);
            if(++checked == checkThrshld)
                break;
        }
        if(checked == checkThrshld)
            break;
    }

    //stop timer
    high_resolution_clock::time_point stopTimer = high_resolution_clock::now();
    auto timerDuration = duration_cast<microseconds>(stopTimer - startTimer);

    //gather results
    vector<tuple<int, Image*>> result;
    queue.transferToVector(&result);
    return make_tuple(result, timerDuration);
}