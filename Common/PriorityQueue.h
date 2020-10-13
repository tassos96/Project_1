#ifndef PROJECT_TASK1_PRIORITYQUEUE_H
#define PROJECT_TASK1_PRIORITYQUEUE_H

#include <queue>
#include <tuple>
#include "image.h"
#include "Distance.h"

using namespace std;

class Compare {
public:
    bool operator() (tuple<int, Image *> &t1, tuple<int, Image *> &t2) {
        return get<0>(t1) < get<0>(t2);
    }
};

class PriorityQueue {
private:
    priority_queue<tuple<int, Image *>,
                    vector< tuple<int, Image *> >,
                    Compare> queue;

public:
    void tryInsert(Image *, Image *, int );
    void transferToVector(vector<tuple<int, Image*>> *);
    void insert(Image *, int);

};


#endif //PROJECT_TASK1_PRIORITYQUEUE_H
