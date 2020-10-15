#ifndef PROJECT_TASK1_RANGESEARCH_H
#define PROJECT_TASK1_RANGESEARCH_H

#include <unordered_map>
#include <queue>
#include <tuple>
#include <limits>

#include "../Common/image.h"
#include "../Common/Distance.h"
#include "../Structures/lsh.h"
#include "../Structures/HyperCube.h"

vector<tuple<int,Image*>> aproxRangeSrch(Image* queryImage,
                                        Lsh* structure,
                                        double radius);

vector<tuple<int, Image*>> aproxRangeSrch(Image* queryImage,
                                          HyperCube* structure,
                                          int checkThrshld,
                                          int maxProbes,
                                          double radius);

#endif //PROJECT_TASK1_RANGESEARCH_H
