#ifndef PROJECT_TASK1_PRIORITYQUEUE_H
#define PROJECT_TASK1_PRIORITYQUEUE_H

#include <queue>
#include <tuple>
#include "image.h"
#include "Distance.h"

using namespace std;

auto comp = [](const tuple<int, Image *>& i1,
                const tuple<int, Image *>& i2)
                    {return get<0>(i1) < get<0>(i2); };

class PriorityQueue {
private:
    priority_queue<tuple<int, Image *>,
                    vector< tuple<int, Image *> >,
                    decltype(comp)> * queue;

public:
    PriorityQueue();
    ~PriorityQueue();

    void tryInsertQueue(Image *, Image *, int );
    void transferToVector(vector<tuple<int, Image*>> *);
    void insertQueue(Image *, int);

};


#endif //PROJECT_TASK1_PRIORITYQUEUE_H
