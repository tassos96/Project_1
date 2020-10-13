#include "dataset.h"

Dataset::Dataset(string &fileName) {
    this->data = new unordered_map<int, Image *>;

    this->readData(fileName);

}

Dataset::~Dataset(){
    for (int i = 0; i < this->imgNum; ++i) {
        delete this->data->at(i);
    }
    delete this->data; /* delete ptr to vector */

    cout << "Destructor of reader" << endl;
}

void Dataset::readData(string &fileName) {
    ifstream inpFile(fileName, ios_base::binary);
    if(!inpFile.is_open())
        throw runtime_error("File " + fileName + " cannot be opened.");

    inpFile.seekg(sizeof(int)); /* skip magical number */

    char * p = (char *)&this->imgNum;
    for (int i = 0; i < sizeof(int) * 3; ++i) { /* read 3 ints */
        if(i == sizeof(int)) /* done reading bytes of image # */
            p = (char *)&this->rows;
        else if(i == sizeof(int)*2) /* done reading bytes of rows */
            p = (char *)&this->columns;
        if(i == sizeof(int) || i == sizeof(int)*2 || i == 0)
            p += sizeof(int) - 1; /* set pointer at the mst byte of integers */

        inpFile.get(*p--);
    }

    cout << "Number of images:" << this->imgNum << endl;
    cout << "Number of rows:" << this->rows << endl;
    cout << "Number of columns:" << this->columns << endl;


    for (int i = 0; i < this->imgNum; ++i) {
        Image * newImg = new Image(i);
        for (int j = 0; j < this->rows*this->columns; ++j) {
            newImg->setPixel(inpFile.get());
        }
        pair<int, Image *> newPair(i, newImg);
        this->data->insert(newPair);
    }

    inpFile.close();
}

unordered_map<int, Image *> *Dataset::getImages() const {
    return this->data;
}

int Dataset::getImageNum() const {
    return this->imgNum;
}

int Dataset::getDimensions() const {
    return this->rows * this->columns;
}

void Dataset::unmarkAllImages() {
    for(int i = 0; i < this->data->size(); ++i)
        this->data->at(i)->unmarkImage();
}