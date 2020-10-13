#ifndef PROJECT_TASK1_UTILS_H
#define PROJECT_TASK1_UTILS_H

#include "image.h"
#include <tuple>
#include <chrono>
#include <unordered_map>
#include <cmath>
#include "Distance.h"

using namespace std;
using namespace std::chrono;

void printResults(tuple<vector<tuple<int,Image*>>, microseconds> &apprNearestImages,
                  tuple<vector<tuple<int,Image*>>, microseconds> &exactNearestImages,
                  vector<tuple<int,Image*>> &apprRangeSrchImages,
                  Image * queryImg);

void unmarkImgs(unordered_map<int, Image*> * imgs, int imgNum);

void getNearbyVertices(string currentVertex,
                       int i,
                       int changesLeft);

#endif //PROJECT_TASK1_UTILS_H
