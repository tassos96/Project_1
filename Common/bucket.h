

#ifndef PROJECT_TASK1_BUCKET_H
#define PROJECT_TASK1_BUCKET_H

#include <vector>
#include "image.h"

class Bucket{
private:
    vector<Image *> *images;
public:
    Bucket();
    virtual ~Bucket();
    void insertImage(Image *);
};

#endif //PROJECT_TASK1_BUCKET_H
