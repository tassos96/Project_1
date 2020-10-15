#include "HyperCube.h"

F::F(int imgDimension, double h_W, int h_div):h(imgDimension, h_W, h_div) {}

unsigned char F::rollTheDice(vector<unsigned char> *pixels){
    int hashReslt = this->h.hashResult(pixels);
    try {
        return this->diceRolls.at(hashReslt);
    }
    catch (out_of_range &) {
        unsigned seed = system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(0, 1);
        this->diceRolls.insert(pair<int,unsigned char>(hashReslt,distribution(generator)));
        return this->diceRolls.at(hashReslt);
    }
}

HyperCube::HyperCube(int imgDimension,
                     double h_W,
                     int h_div,
                     int cubeDimension) {
    this->cubeDimension = cubeDimension;

    for (int i = 0; i < this->cubeDimension; ++i) // create f functions
        this->projectors.push_back(new F(imgDimension, h_W, h_div));
}


HyperCube::~HyperCube(){
    for (int i = 0; i < this->cubeDimension; ++i)
        delete this->projectors.at(i);

    for (pair<string, Bucket *> element : this->vertices)
        delete element.second;
}

string HyperCube::getVertexIdx(Image * img) {
    string toRet;
    for (int i = 0; i < this->cubeDimension; ++i)
        toRet += this->projectors.at(i)->rollTheDice(img->getPixels());

    return toRet;
}

Bucket * HyperCube::getVertex(Image * img) {
    string idx = getVertexIdx(img);
    try {
        return this->vertices.at(idx);
    }
    catch (out_of_range &) {
        return nullptr;
    }
}

void HyperCube::splitIntoVertices(int imgNum, unordered_map<int, Image *> * imgs) {
    for (int i = 0; i < imgNum; ++i) {
        string vertex = this->getVertexIdx(imgs->at(i));
        try {
            this->vertices.at(vertex)->insertImage(imgs->at(i));
        }
        catch (out_of_range &) {
            this->vertices.insert(pair<string, Bucket *>(vertex,new Bucket));
            this->vertices.at(vertex)->insertImage(imgs->at(i));
        }
    }
}

unordered_map<string, Bucket *> HyperCube::getVertices() {
    return this->vertices;
}