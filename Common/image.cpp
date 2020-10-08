//
// Created by sysgod on 07/10/2020.
//

#include "image.h"

Image::Image(int id) {
    this->id = id;
    this->pixels = new vector<unsigned char>();
}

int Image::getId() {
    return this->id;
}

Image::~Image() {
    this->pixels->clear();
    delete pixels;
//    cout << "Destructor of image" << endl;
}

void Image::setPixel(unsigned char pxl) {
    this->pixels->push_back(pxl);
}