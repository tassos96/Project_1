#ifndef PROJECT_TASK1_READER_H
#define PROJECT_TASK1_READER_H

#include <vector>
#include <fstream>

#include "image.h"

using namespace std;

class Reader {
private:
    vector<Image *> * data;
    void readData(string &);

public:
    Reader(string &);
    virtual ~Reader();

    vector<Image *> *getData() const;

};


#endif //PROJECT_TASK1_READER_H