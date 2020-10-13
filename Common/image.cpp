#include "image.h"

Image::Image(int id) {
    this->id = id;
    this->marked = false;
    this->markedRange = false;
    this->pixels = new vector<unsigned char>;
    this->g_results = new vector<unsigned int>;
}

int Image::getId() {
    return this->id;
}

Image::~Image() {
    delete this->pixels;
    delete this->g_results;
//    cout << "Destructor of image" << endl;
}

void Image::setPixel(unsigned char pxl) {
    this->pixels->push_back(pxl);
}

vector<unsigned char> *Image::getPixels() const {
    return this->pixels;
}

void Image::keepHashResult(unsigned int toKeep) {
    this->g_results->push_back(toKeep);
}

void Image::markImage() {
    this->marked = true;
}

bool Image::isMarked() {
    return this->marked;
}

void Image::markImageRange() {
    this->markedRange = true;
}

bool Image::isMarkedRange() {
    return this->markedRange;
}