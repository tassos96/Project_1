#include "HyperCube.h"

F::F(int imgDimension, double h_W, int h_div):h(imgDimension, h_W, h_div) {}

char F::flipTheCoin(vector<unsigned char> *pixels){
    int hashReslt = this->h.hashResult(pixels);
    try {
        return this->coinFlips.at(hashReslt);
    }
    catch (out_of_range &) {
        unsigned seed = system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(0, 1);
        int coinSide = distribution(generator);
        char choice = coinSide == 0 ? '0' : '1';
        this->coinFlips.insert(pair<int, char>(hashReslt,choice));
        return this->coinFlips.at(hashReslt);
    }
}

HyperCube::HyperCube(int imgDimension,
                     double h_W,
                     int h_div,
                     int cubeDimension,
                     int imgNum,
                     vector<Image *> *imgs) {
    this->cubeDimension = cubeDimension;

    for (int i = 0; i < this->cubeDimension; ++i) // create f functions
        this->projectors.push_back(new F(imgDimension, h_W, h_div));

    this->splitIntoVertices(imgNum, imgs); // place train data into vertices
}


HyperCube::~HyperCube(){
    for (int i = 0; i < this->cubeDimension; ++i)
        delete this->projectors.at(i);

    for (pair<string, Bucket *> element : this->vertices)
        delete element.second;
}

string HyperCube::getVertexIdx(vector<unsigned char> * img) {
    string toRet;
    for (int i = 0; i < this->cubeDimension; ++i)
        toRet += this->projectors.at(i)->flipTheCoin(img);

    return toRet;
}

Bucket * HyperCube::getVertexByImg(Image * img) {
    string idx = getVertexIdx(img->getPixels());
    try {
        return this->vertices.at(idx);
    }
    catch (out_of_range &) {
        return nullptr;
    }
}

Bucket * HyperCube::getVertexByIdx(const string &idx) {
    try {
        return this->vertices.at(idx);
    }
    catch (out_of_range &) {
        return nullptr;
    }
}

void HyperCube::splitIntoVertices(int imgNum, vector<Image *> * imgs) {
    for (int i = 0; i < imgNum; ++i) {
        string vertex = this->getVertexIdx(imgs->at(i)->getPixels());
        try {
            this->vertices.at(vertex)->insertImage(imgs->at(i));
        }
        catch (out_of_range &) {
            this->vertices.insert(pair<string, Bucket *>(vertex,new Bucket));
            this->vertices.at(vertex)->insertImage(imgs->at(i));
        }
    }
}