#include "ExactNN.h"

tuple<vector<tuple<int,Image*>>, microseconds> exactNN(Image* queryImage,
                                                       unordered_map<int, Image *> *datasetImages,
                                                       int numNeighbors){
    auto my_comp =
            [](const tuple<int, Image *>& i1,
               const tuple<int, Image *>& i2)
            { return get<0>(i1) < get<0>(i2); };

    priority_queue<tuple<int, Image *>,
            vector< tuple<int, Image *> >,
            decltype(my_comp)> queue(my_comp);

    high_resolution_clock::time_point startTimer = high_resolution_clock::now(); //Start timer

    //For every image on dataset
    for(int i = 0; i < datasetImages->size(); ++i) {
        int newDist = manhattanDistance(queryImage->getPixels(), datasetImages->at(i)->getPixels());
        if(queue.size() < numNeighbors)
            queue.push(make_tuple(newDist, datasetImages->at(i)));
        else if(newDist < get<0>(queue.top())) {
            queue.pop();
            queue.push(make_tuple(newDist, datasetImages->at(i)));
        }
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
