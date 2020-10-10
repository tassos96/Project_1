#include "dataset.h"

Dataset::Dataset(string &fileName) {
    this->data = new vector<Image *>();

    this->readData(fileName);

}

Dataset::~Dataset(){
    vector<Image *>::iterator it;
    for (it = this->data->begin(); it < this->data->end() ; ++it) { /* free all Images */
        delete *it;
    }
    delete this->data; /* delete ptr to vector */

    cout << "Destructor of reader" << endl;
}

void Dataset::readData(string &fileName) {
    ifstream inpFile(fileName, ios_base::binary);
    if(!inpFile.is_open())
        throw runtime_error("File " + fileName + " cannot be opened.");

    inpFile.seekg(sizeof(int)); /* skip magical number */

    int imgNum;
    char * p = (char *)&imgNum;
    for (int i = 0; i < sizeof(int) * 3; ++i) { /* read 3 ints */
        if(i == sizeof(int)) /* done reading bytes of image # */
            p = (char *)&this->rows;
        else if(i == sizeof(int)*2) /* done reading bytes of rows */
            p = (char *)&this->columns;
        if(i == sizeof(int) || i == sizeof(int)*2 || i == 0)
            p += sizeof(int) - 1; /* set pointer at the mst byte of integers */

        inpFile.get(*p--);
    }

    cout << "Number of images:" << imgNum << endl;
    cout << "Number of rows:" << this->rows << endl;
    cout << "Number of columns:" << this->columns << endl;


    for (int i = 0; i < imgNum; ++i) {
        Image * newImg = new Image(i);
        for (int j = 0; j < this->rows*this->columns; ++j) {
            newImg->setPixel(inpFile.get());
        }
        this->data->push_back(newImg);
    }

    inpFile.close();
}

vector<Image *> *Dataset::getData() const {
    return data;
}
