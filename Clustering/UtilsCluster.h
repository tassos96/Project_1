#ifndef PROJECT_TASK1_UTILSCLUSTER_H
#define PROJECT_TASK1_UTILSCLUSTER_H

#include "image.h"
#include "../Common/Distance.h"
#include <cmath>
#include <algorithm>

using namespace std;

vector<unsigned char> *getMedian(vector<Image *> * imgs, int dimension);

int binSearch(const vector<double> &probs, int start, int end, const double &val);

vector<Image *> kMeansPPlus(vector<Image *> *imgs, int numOfCentroids);

int closestClusterIdx(Image * img, vector<vector<unsigned char> *> *centroids);

#endif //PROJECT_TASK1_UTILSCLUSTER_H
