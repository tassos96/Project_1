#ifndef PROJECT_TASK1_DISTANCE_H
#define PROJECT_TASK1_DISTANCE_H

#include <vector>
#include <unordered_map>
#include "image.h"
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <cmath>
#include "../Algorithms/ExactNN.h"

using namespace std;

//Function that calculates the manhattan distance between two images
int manhattanDistance(vector<unsigned char> * firstImagePixels, vector<unsigned char> * secondImagePixels);
double calcW(unordered_map<int, Image *> * imgs, double samplePrcnt, int imgNum);

#endif //PROJECT_TASK1_DISTANCE_H
