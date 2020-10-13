#include "Utils.h"

void printResults(tuple<vector<tuple<int,Image*>>, microseconds> &apprNearestImages,
                  tuple<vector<tuple<int,Image*>>, microseconds> &exactNearestImages,
                  tuple<vector<tuple<int,Image*>>, microseconds> &apprRangeSrchImages,
                  Image * queryImg) {
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

            cout << "distanceLSH: " << get<0>(vAppr.at(j - diff)) << endl;
            cout << "distanceTrue: " << get<0>(vExact.at(j)) << endl;
        }
        else {
            cout << "Approximate Nearest neighbour-"<< vExact.size() - j
                 << ": NOT FOUND" << endl;
            cout << "Exact Nearest neighbour-"<< vExact.size() - j
                 << ": " << get<1>(vExact.at(j))->getId() << endl;

            cout << "distanceLSH: -"<< endl;
            cout << "distanceTrue: " << get<0>(vExact.at(j)) << endl;
        }

    }
    cout << "tLSH: " << get<1>(apprNearestImages).count() / 1000000.0 << "s" << endl;
    cout << "tTrue: " << get<1>(exactNearestImages).count() / 1000000.0 << "s" << endl;

    printRangeNrstImages(apprRangeSrchImages);
}

void printRangeNrstImages(tuple<vector<tuple<int,Image*>>, microseconds> &apprRangeSrchImages) {
    vector<tuple<int,Image*>> &vec = get<0>(apprRangeSrchImages);
    cout << "R-near neighbors: " << endl;
    for(int i = vec.size()-1; i >= 0; --i) {
        cout << "\tImage_" << get<1>(vec.at(i))->getId() << " Distance: " << get<0>(vec.at(i)) << endl;
    }
    cout << "~~~~~~~~~~~" << endl << endl;
}

void unmarkImgs(unordered_map<int, Image*> * imgs, int imgNum) {
    for (int i = 0; i < imgNum; ++i)
        imgs->at(i)->unmarkImage();
}