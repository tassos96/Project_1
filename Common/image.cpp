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
//    delete pixels;
    this->pixels->clear();
    cout << "Destructor of image" << endl;
}

void Image::setPixel(unsigned char pxl) {
    this->pixels->push_back(pxl);
}

void Image::printPixels() {
    vector<unsigned char>::iterator it;
    cout << "*******" << endl;
    int x = 1;
    for (int i = 0; i < this->pixels->size(); i++) {
        cout << this->pixels->at(i) << " ";
        if(x % 100 == 0)
            cout << endl;
        x++;
    }
    cout << "*******" << endl;
}