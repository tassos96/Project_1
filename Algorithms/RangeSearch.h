#ifndef PROJECT_TASK1_RANGESEARCH_H
#define PROJECT_TASK1_RANGESEARCH_H

#include <unordered_map>
#include <queue>
#include <tuple>
#include <limits>
#include <chrono>


#include "../Common/image.h"
#include "../Common/Distance.h"
#include "../Classifiers/lsh.h"

tuple<vector<tuple<int,Image*>>, microseconds> aproxRangeSrch(Image* queryImage,
                                                            Lsh* structure,
                                                            double radius);

#endif //PROJECT_TASK1_RANGESEARCH_H
