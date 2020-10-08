#include "Distance.h"

double manhattanDistance(vector<unsigned char> * firstImagePixels, vector<unsigned char> * secondImagePixels) {
    double distance = 0.0f;   //Distance to return
    for(int i = 0; i < firstImagePixels->size(); ++i) //For every pixel calculate distance
    {
        double dif = abs(firstImagePixels->at(i) - secondImagePixels->at(i));
        distance += dif;
    }
    return distance; // return distance of images
}
