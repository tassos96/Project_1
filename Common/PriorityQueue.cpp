#include "PriorityQueue.h"

void PriorityQueue::tryInsert(Image *queryImg, Image *newImg, int numNeighbors) {
    int newDist = manhattanDistance(queryImg->getPixels(), newImg->getPixels());
    if(this->queue.size() < numNeighbors)
        this->queue.push(make_tuple(newDist, newImg));
    else if(newDist < get<0>(queue.top())) {
        this->queue.pop();
        this->queue.push(make_tuple(newDist, newImg));
    }
}

void PriorityQueue::insert(Image *newImg, int newDist) {
    this->queue.push(make_tuple(newDist, newImg));
}

void PriorityQueue::transferToVector(vector<tuple<int, Image *>> * vec) {
    while(!queue.empty()) {
        vec->push_back(queue.top());
        queue.pop();
    }
}