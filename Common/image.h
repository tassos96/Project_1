#ifndef PROJECT_TASK1_IMAGE_H
#define PROJECT_TASK1_IMAGE_H

#include <iostream>
#include <vector>


using namespace std;

class Image {
private:
    int id;
    bool marked;
    bool assignedToCluster;
    vector<unsigned char> *pixels;

public:
    Image(int);
    ~Image();
    int getId();
    void setPixel(unsigned char);

    vector<unsigned char> *getPixels() const;
    bool isMarked();
    void markImage();
    void unmarkImage();
    bool isAssignedToClst() const;
    void assignImageToClst();
    void unassignImageFromClst();
};


#endif //PROJECT_TASK1_IMAGE_H