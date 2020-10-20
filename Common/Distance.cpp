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

double calcW(vector<Image *> * imgs, double samplePrcnt, int imgNum) {
    int numIndexes = (samplePrcnt / 100.0) * imgNum;
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

    if(dstnc == 0 || numIndexes == 0) {
        throw runtime_error("W is 0, check sample percentage parameter in \"parameters.conf\" file");
    }

    return dstnc / numIndexes;
}


int hammingDistance(string str1, string str2) {
    // strings are always of the same length since they refer to hypercube vertices
    int toRet = 0;
    for (int i = 0; i < str1.length(); ++i)
        toRet += str1[i] == str2[i] ? 0 : 1;

    return toRet;
}