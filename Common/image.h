//
// Created by sysgod on 07/10/2020.
//

#ifndef PROJ1_EMIRIS_IMAGE_H
#define PROJ1_EMIRIS_IMAGE_H

#include <iostream>
#include <vector>


using namespace std;

class Image {
private:
    int id;
    vector<unsigned char> * pixels;

public:
    Image(int);
    ~Image();

    int getId();
    void setPixel(unsigned char);
    void printPixels();
};


#endif //PROJ1_EMIRIS_IMAGE_H
