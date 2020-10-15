#ifndef PROJECT_TASK1_APROXNN_H
#define PROJECT_TASK1_APROXNN_H

#include <unordered_map>
#include <queue>
#include <tuple>
#include <limits>
#include <chrono>


#include "../Common/image.h"
#include "../Common/PriorityQueue.h"
#include "../Common/Distance.h"
#include "../Structures/lsh.h"
#include "../Structures/HyperCube.h"

using namespace std;
using namespace std::chrono;

tuple<vector<tuple<int,Image*>>, microseconds> aproxKNN(Image* queryImage,
                                                        Lsh* structure,
                                                        int numNeighbors = 1);

tuple<vector<tuple<int,Image*>>, microseconds> aproxKNN(Image* queryImage,
                                                        HyperCube* structure,
                                                        int checkThrshld,
                                                        int maxProbes,
                                                        int numNeighbors = 1);

#endif //PROJECT_TASK1_APROXNN_H
