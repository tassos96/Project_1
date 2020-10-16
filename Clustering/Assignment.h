#ifndef PROJECT_TASK1_ASSIGNMENT_H
#define PROJECT_TASK1_ASSIGNMENT_H

#include "../Common/image.h"
#include "UtilsCluster.h"
#include "Cluster.h"

void lloydAssign(const vector<Cluster *> & clusters);
void lloydAssign(const vector<Cluster *> & clusters, vector<Image *> *imgs); // first assignment

#endif //PROJECT_TASK1_ASSIGNMENT_H
