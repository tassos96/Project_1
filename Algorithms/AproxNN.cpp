#include "AproxNN.h"

tuple<vector<tuple<int,Image*>>, microseconds> aproxKNN(Image* queryImage,
                                                        Lsh* structure,
                                                        int numNeighbors) {
    auto my_comp =
            [](const tuple<int, Image *>& i1,
                const tuple<int, Image *>& i2)
            { return get<0>(i1) < get<0>(i2); };

    priority_queue<tuple<int, Image *>,
                   vector< tuple<int, Image *> >,
                   decltype(my_comp)> queue(my_comp);
    //start timer
    high_resolution_clock::time_point startTimer = high_resolution_clock::now();
    // number of lsh tables
    int numTables = structure->getNumTables();
    int checked = 0;
    for (int i = 0; i < numTables; ++i) {
        LshTable *tbl = structure->getHashTable(i);
        tuple<int, Bucket *>bucketTpl = tbl->getBucket(queryImage);
        Bucket * buckPtr = get<1>(bucketTpl);
        if(buckPtr == nullptr)
            continue;
        vector<Image *> *buckImgs = buckPtr->getImages();
        for (int j = 0; j < buckImgs->size(); ++j) {
            if(buckImgs->at(j)->isMarked())
                continue;
            buckImgs->at(j)->markImage();
            int newDist = manhattanDistance(queryImage->getPixels(), buckImgs->at(j)->getPixels());
            if(queue.size() < numNeighbors)
                queue.push(make_tuple(newDist, buckImgs->at(j)));
            else if(newDist < get<0>(queue.top())) {
                queue.pop();
                queue.push(make_tuple(newDist, buckImgs->at(j)));
            }
            if(++checked > (100*numTables)){
                cout << "checked many images" << endl;
                break;
            }

        }
        if(checked > (100*numTables))
            break;
    }
    //stop timer
    high_resolution_clock::time_point stopTimer = high_resolution_clock::now();
    auto timerDuration = duration_cast<microseconds>(stopTimer - startTimer);
    //gather results
    vector<tuple<int, Image*>> result;
    while(!queue.empty()) {
        result.push_back(queue.top());
        queue.pop();
    }
    return make_tuple(result, timerDuration);
}

