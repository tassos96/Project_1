#ifndef PROJECT_TASK1_BUCKET_H
#define PROJECT_TASK1_BUCKET_H

#include <vector>
#include "image.h"

class Bucket{
private:
    vector<Image *> *images;
public:
    Bucket();
    ~Bucket();
    void insertImage(Image *);
    vector<Image *> *getImages();
};

#endif //PROJECT_TASK1_BUCKET_H
