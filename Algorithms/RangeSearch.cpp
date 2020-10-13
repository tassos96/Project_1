#include "RangeSearch.h"

#define CHECKED_FACTOR 100

tuple<vector<tuple<int,Image*>>, microseconds> aproxRangeSrch(Image* queryImage,
                                                                Lsh* structure,
                                                                double radius) {
    PriorityQueue queue;

    //start timer
    high_resolution_clock::time_point startTimer = high_resolution_clock::now();

    // number of lsh tables
    int numTables = structure->getNumTables();

    int checked = 0;
    cout << endl << "*** RANGE SEARCH ***" << endl;
    for (int i = 0; i < numTables; ++i) {
        LshTable *tbl = structure->getHashTable(i);
        tuple<int, Bucket *> bucketTpl = tbl->getBucket(queryImage);
        Bucket *buckPtr = get<1>(bucketTpl);
        if (buckPtr == nullptr)
            continue;
        cout << "Checking bucket #" << get<0>(bucketTpl) << " of table #" << i << endl;
        vector<Image *> *buckImgs = buckPtr->getImages();
        for (int j = 0; j < buckImgs->size(); ++j) {
            if(buckImgs->at(j)->isMarked())
                continue;
            buckImgs->at(j)->markImage();

            int newDist = manhattanDistance(queryImage->getPixels(), buckImgs->at(j)->getPixels());
            if(newDist <= radius)
                queue.insert(buckImgs->at(j), newDist);

//            if(++checked > (2*CHECKED_FACTOR*numTables)){
//                cout << "checked many images" << endl;
//                break;
//            }
        }
//        if(checked > (2*CHECKED_FACTOR*numTables))
//            break;
    }

    //stop timer
    high_resolution_clock::time_point stopTimer = high_resolution_clock::now();
    auto timerDuration = duration_cast<microseconds>(stopTimer - startTimer);

    //gather results
    vector<tuple<int, Image*>> result;
    queue.transferToVector(&result);
    return make_tuple(result, timerDuration);
}
