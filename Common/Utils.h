#ifndef PROJECT_TASK1_UTILS_H
#define PROJECT_TASK1_UTILS_H

#include "image.h"
#include <tuple>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

void printResults(tuple<vector<tuple<int,Image*>>, microseconds> &apprNearestImages,
                  tuple<vector<tuple<int,Image*>>, microseconds> &exactNearestImages,
                  Image * queryImg);

#endif //PROJECT_TASK1_UTILS_H
