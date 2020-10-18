#ifndef PROJECT_TASK1_ASSIGNMENT_H
#define PROJECT_TASK1_ASSIGNMENT_H

#include "../Common/Utils.h"
#include "UtilsCluster.h"
#include "Cluster.h"
#include "../Structures/lsh.h"
#include "../Algorithms/RangeSearch.h"

void lloydAssign(const vector<Cluster *> & clusters, vector<Image *> *imgs); // first assignment
void lloydAssign(const vector<Cluster *> & clusters, int & assignmentsNum);


#endif //PROJECT_TASK1_ASSIGNMENT_H
