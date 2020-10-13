#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {
    this->queue = new priority_queue<tuple<int, Image *>,
                                    vector< tuple<int, Image *> >,
                                    decltype(comp)>(comp);
}

PriorityQueue::~PriorityQueue() {
    delete this->queue;
}

void PriorityQueue::tryInsertQueue(Image *queryImg, Image *newImg, int numNeighbors) {
    int newDist = manhattanDistance(queryImg->getPixels(), newImg->getPixels());
    if(this->queue->size() < numNeighbors)
        this->queue->push(make_tuple(newDist, newImg));
    else if(newDist < get<0>(queue->top())) {
        this->queue->pop();
        this->queue->push(make_tuple(newDist, newImg));
    }
}

void PriorityQueue::insertQueue(Image *newImg, int newDist) {
    this->queue->push(make_tuple(newDist, newImg));
}

void PriorityQueue::transferToVector(vector<tuple<int, Image *>> * vec) {
    while(!queue->empty()) {
        vec->push_back(queue->top());
        queue->pop();
    }
}