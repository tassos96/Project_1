#ifndef PROJECT_TASK1_BUCKET_H
#define PROJECT_TASK1_BUCKET_H

#include <vector>
#include "image.h"

class Bucket{
private:
    vector<Image *> *images;
    vector<unsigned int> *g_hash_results;
public:
    Bucket();
    ~Bucket();
    void insertImage(Image *);
    vector<Image *> *getImages();
    void insertHashRes(unsigned int res);
    vector<unsigned int> *getHashReslts();
};

#endif //PROJECT_TASK1_BUCKET_H
