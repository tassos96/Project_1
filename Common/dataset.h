#ifndef PROJECT_TASK1_DATASET_H
#define PROJECT_TASK1_DATASET_H

#include <vector>
#include <fstream>
#include <unordered_map>

#include "image.h"

using namespace std;

class Dataset {
private:
    int rows;
    int columns;
    int imgNum;
    unordered_map<int, Image *> * data;
    void readData(string &);

public:
    Dataset(string &);
    virtual ~Dataset();

    unordered_map<int, Image *> *getImages() const;
    int getImageNum() const;
    int getDimensions() const;
};


#endif //PROJECT_TASK1_DATASET_H