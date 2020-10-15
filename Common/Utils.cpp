#include "Utils.h"

void printRangeNrstImages(vector<tuple<int,Image*>> &apprRangeSrchImages) {
    vector<tuple<int,Image*>> &vec = apprRangeSrchImages;
    cout << "R-near neighbors: " << endl;
    for(int i = 0; i < vec.size(); ++i) {
        printf("\t %-3d -> %-2d\n", i, get<1>(vec.at(i))->getId());
    }
    cout << "~~~~~~~~~~~" << endl << endl;
}

string distanceOutput(bool isLsh) {
    return isLsh ? "distanceLSH: " : "distanceHypercube: ";
}

void printResults(tuple<vector<tuple<int,Image*>>, microseconds> &apprNearestImages,
                  tuple<vector<tuple<int,Image*>>, microseconds> &exactNearestImages,
                  vector<tuple<int,Image*>> &apprRangeSrchImages,
                  Image * queryImg,
                  bool isLsh) {
    vector<tuple<int,Image*>> &vAppr = get<0>(apprNearestImages);
    vector<tuple<int,Image*>> &vExact = get<0>(exactNearestImages);

    cout << "Query: " << queryImg->getId() << endl;
    int diff = (int)vExact.size() - (int)vAppr.size();
    for (int j = (int)vExact.size()-1; j >= 0; --j) {
        if(j - diff >= 0) {
            cout << "Approximate Nearest neighbour-"<< vExact.size() - j
                 << ": " << get<1>(vAppr.at(j - diff))->getId() << endl;
            cout << "Exact Nearest neighbour-"<< vExact.size() - j
                 << ": " << get<1>(vExact.at(j))->getId() << endl;

            cout << distanceOutput(isLsh) << get<0>(vAppr.at(j - diff)) << endl;
            cout << "distanceTrue: " << get<0>(vExact.at(j)) << endl;
        }
        else {
            cout << "Approximate Nearest neighbour-"<< vExact.size() - j
                 << ": NOT FOUND" << endl;
            cout << "Exact Nearest neighbour-"<< vExact.size() - j
                 << ": " << get<1>(vExact.at(j))->getId() << endl;

            cout << distanceOutput(isLsh) << "-"<< endl;
            cout << "distanceTrue: " << get<0>(vExact.at(j)) << endl;
        }

    }
    string timeMessg = isLsh ? "tLSH: " : "tHypercube: ";
    cout << timeMessg << get<1>(apprNearestImages).count() / 1000000.0 << "s" << endl;
    cout << "tTrue: " << get<1>(exactNearestImages).count() / 1000000.0 << "s" << endl;

    printRangeNrstImages(apprRangeSrchImages);
}

void unmarkImgs(unordered_map<int, Image*> * imgs, int imgNum) {
    for (int i = 0; i < imgNum; ++i)
        imgs->at(i)->unmarkImage();
}

void getNearbyVertices(vector<string> &vec,
                       string currentVertex,
                       int i,
                       int changesLeft) {
    if(changesLeft == 0) {
        vec.push_back(currentVertex);
        return;
    }
    if(i < 0)
        return;
    //flip current bit
    currentVertex[i] = currentVertex[i] == '0' ? '1' : '0';
    getNearbyVertices(vec, currentVertex, i - 1, changesLeft - 1);
    //or dont flip it (flip it again to undo)
    currentVertex[i] = currentVertex[i] == '0' ? '1' : '0';
    getNearbyVertices(vec, currentVertex, i - 1, changesLeft);
}

void getVerticesToCheck(vector<string> &vec,
                        string &currentVertex,
                        int maxDistance) {
    for(int curDist = 0; curDist <= maxDistance; ++curDist)
        getNearbyVertices(vec, currentVertex, currentVertex.length() - 1, curDist);
}

vector<unsigned char> *getMedian(vector<Image *> * imgs, int dimension) {
    // a vector containing median for each dimension
    vector<unsigned char> * toRet = new vector<unsigned char>;

    for (int i = 0; i < dimension; ++i) {
        vector<unsigned char> dim_i_pixels;
        dim_i_pixels.reserve(imgs->size());
        for (Image * img: *imgs) { // gather all pixels for each dimension
            dim_i_pixels.push_back(img->getPixels()->at(i));
        }
        // sort in order to find the median
        sort(dim_i_pixels.begin(), dim_i_pixels.end());
        int medianIdx = floor((dim_i_pixels.size()-1) / 2);
        toRet->push_back(dim_i_pixels.at(medianIdx)); // keep the median of current dimension
    }

    return toRet;
}