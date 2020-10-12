#include "Distance.h"

int manhattanDistance(vector<unsigned char> * firstImagePixels, vector<unsigned char> * secondImagePixels) {
    int distance = 0;   //Distance to return
    for(int i = 0; i < firstImagePixels->size(); ++i) //For every pixel calculate distance
    {
        int dif = abs(firstImagePixels->at(i) - secondImagePixels->at(i));
        distance += dif;
    }
    return distance; // return distance of images
}

double calcW(unordered_map<int, Image *> * imgs, double samplePrcnt, int imgNum) {
    int numIndexes = (samplePrcnt / 100.0) * imgNum;
    cout << "Sample size " << numIndexes << endl;
    vector<int> idx(imgNum); // vector with all image ids.
    iota(idx.begin(), idx.end(), 0); // ids.
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    shuffle(idx.begin(),idx.end(),generator);
    double dstnc = 0.0;
    for (int i = 0; i < numIndexes; ++i) {
        /* calculate nearest neighbour from sample */
        int minDistance = numeric_limits<int>::max();
        for (int j = 0; j < numIndexes; ++j) {
            if(i == j)
                continue;
            int currentDistance = manhattanDistance(imgs->at(idx.at(i))->getPixels(),
                                                    imgs->at(idx.at(j))->getPixels());
            if(currentDistance < minDistance) {
                minDistance = currentDistance;
            }
        }
        dstnc += minDistance;
    }
    return dstnc / numIndexes;
}