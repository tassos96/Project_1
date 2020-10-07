//
// Created by sysgod on 07/10/2020.
//

#include "reader.h"

Reader::Reader(string &fileName) {
    this->data = new vector<Image>();

    this->readData(fileName);

};

Reader::~Reader(){
    vector<Image>::iterator it;
//    for (it = this->data->begin(); it <= this->data->end(); it++) {
//        delete &it;
//    }
    this->data->clear();

    cout << "Destructor of reader" << endl;
};

void Reader::readData(string &fileName) {
    ifstream inpFile(fileName, ios_base::binary);
    if(!inpFile.is_open())
        throw runtime_error("File " + fileName + " cannot be opened.");

    inpFile.seekg(sizeof(int)); /* skip magical number */

    int imgNum, rows, columns;
    char * p = (char *)&imgNum;
    for (int i = 0; i < sizeof(int) * 3; ++i) { /* read 3 ints */
        if(i == sizeof(int)) /* done reading bytes of image # */
            p = (char *)&rows;
        else if(i == sizeof(int)*2) /* done reading bytes of rows */
            p = (char *)&columns;
        if(i == sizeof(int) || i == sizeof(int)*2 || i == 0)
            p += sizeof(int) - 1; /* set pointer at the mst byte of integers */

        inpFile.get(*p--);
    }

    cout << "Number of images:" << imgNum << endl;
    cout << "Number of rows:" << rows << endl;
    cout << "Number of columns:" << columns << endl;

    for (int i = 0; i < imgNum; ++i) {
        Image *img = new Image(i);
        this->data->push_back(*img);
        for (int j = 0; j < rows * columns; ++j) {
            unsigned char pxl;
            pxl = inpFile.get();
            img->setPixel(pxl);
        }
        if(i%1000 == 0) {
            img->printPixels();
        }
    }

    inpFile.close();
}