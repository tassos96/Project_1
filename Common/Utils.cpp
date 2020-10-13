#include "Utils.h"

void printRangeNrstImages(vector<tuple<int,Image*>> &apprRangeSrchImages) {
    vector<tuple<int,Image*>> &vec = apprRangeSrchImages;
    cout << "R-near neighbors: " << endl;
    for(int i = 0; i < vec.size(); ++i) {
        printf("\t %-3d -> %-2d\n", i, get<1>(vec.at(i))->getId());
    }
    cout << "~~~~~~~~~~~" << endl << endl;
}

void printResults(tuple<vector<tuple<int,Image*>>, microseconds> &apprNearestImages,
                  tuple<vector<tuple<int,Image*>>, microseconds> &exactNearestImages,
                  vector<tuple<int,Image*>> &apprRangeSrchImages,
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

void unmarkImgs(unordered_map<int, Image*> * imgs, int imgNum) {
    for (int i = 0; i < imgNum; ++i)
        imgs->at(i)->unmarkImage();
}

//vector<string> getNearbyVertices(int hammingDist,
//                                 string currentVertex,
//                                 int start,
//                                 int end) {
//    if(start == end) {
//        return vector<string> {"1","0"};
//    }
//    else if(start > end) {
//        return vector<string>{};
//    }
//    int middl = floor((end + start)/ 2);
//    vector<string>left = getNearbyVertices(hammingDist, currentVertex, start, middl-1);
//    vector<string>right = getNearbyVertices(hammingDist, currentVertex, middl+1, end);
//
//}