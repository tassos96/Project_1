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
