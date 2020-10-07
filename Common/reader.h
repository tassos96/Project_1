//
// Created by sysgod on 07/10/2020.
//

#ifndef PROJ1_EMIRIS_READER_H
#define PROJ1_EMIRIS_READER_H

#include <vector>
#include <fstream>

#include "image.h"

using namespace std;

class Reader {
private:
    vector<Image> * data;
    void readData(string &);

public:
    Reader(string &);
    virtual ~Reader();

};


#endif //PROJ1_EMIRIS_READER_H
