#include "ExactNN.h"

tuple<Image*, int, microseconds> exactNN(Image* queryImage, vector<Image *> *datasetImages){
    //First set minimum distance to a very high value
    int minDistance = numeric_limits<double>::infinity();    //Nearest distance to return
    Image* exactNearestImage = nullptr; //Nearest Image to return
    high_resolution_clock::time_point startTimer = high_resolution_clock::now(); //Start timer
    high_resolution_clock::time_point stopTimer; //Stop timer

    //For every image on dataset
    for(int i = 0; i < datasetImages->size(); i++)
    {
        //Calculate current distance of query image with an image from dataset
        int currentDistance = manhattanDistance(queryImage->getPixels(), datasetImages->at(i)->getPixels());
        //If current distance is smaller than minimum distance then update values to return
        if(currentDistance < minDistance)
        {
            minDistance = currentDistance;
            exactNearestImage = datasetImages->at(i);
        }
    }
    //Stop timer and calculate the microseconds
    stopTimer = high_resolution_clock::now();
    auto timerDuration = duration_cast<microseconds>(stopTimer - startTimer);

    //Construct the tuple to return
    return make_tuple(exactNearestImage, minDistance, timerDuration);
}
