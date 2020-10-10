#ifndef PROJECT_TASK1_DATASET_H
#define PROJECT_TASK1_DATASET_H

#include <vector>
#include <fstream>

#include "image.h"

using namespace std;

class Dataset {
private:
    int rows;
    int columns;
    vector<Image *> * data;
    void readData(string &);

public:
    Dataset(string &);
    virtual ~Dataset();

    vector<Image *> *getData() const;

};


#endif //PROJECT_TASK1_DATASET_H