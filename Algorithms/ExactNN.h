#ifndef PROJECT_TASK1_EXACTNN_H
#define PROJECT_TASK1_EXACTNN_H

#include <unordered_map>
#include <tuple>
#include <limits>
#include <chrono>


#include "../Common/image.h"
#include "../Common/Distance.h"

using namespace std;
using namespace std::chrono;


tuple<Image*, int, microseconds> exactNN(Image* queryImage, unordered_map<int, Image *> *datasetImages);

#endif //PROJECT_TASK1_EXACTNN_H
