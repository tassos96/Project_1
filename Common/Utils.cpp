#include "Utils.h"

void printRangeNrstImages(vector<tuple<int,Image*>> &apprRangeSrchImages, ofstream& outputFile) {
    vector<tuple<int,Image*>> &vec = apprRangeSrchImages;
    outputFile << "R-near neighbors: " << endl;
    for(int i = 0; i < vec.size(); ++i) {
        outputFile << "\t" << get<1>(vec.at(i))->getId() << endl;
    }
    outputFile << "~~~~~~~~~~~" << endl << endl;
}

string distanceOutput(bool isLsh) {
    return isLsh ? "distanceLSH: " : "distanceHypercube: ";
}

void printResults(tuple<vector<tuple<int,Image*>>, microseconds> &apprNearestImages,
                  tuple<vector<tuple<int,Image*>>, microseconds> &exactNearestImages,
                  vector<tuple<int,Image*>> &apprRangeSrchImages,
                  Image * queryImg,
                  bool isLsh,
                  ofstream& outputFile) {
    vector<tuple<int,Image*>> &vAppr = get<0>(apprNearestImages);
    vector<tuple<int,Image*>> &vExact = get<0>(exactNearestImages);

    outputFile << "Query: " << queryImg->getId() << endl;
    int diff = (int)vExact.size() - (int)vAppr.size();
    for (int j = (int)vExact.size()-1; j >= 0; --j) {
        if(j - diff >= 0) {
            outputFile << "Approximate Nearest neighbour-"<< vExact.size() - j
                 << ": " << get<1>(vAppr.at(j - diff))->getId() << endl;
            outputFile << "Exact Nearest neighbour-"<< vExact.size() - j
                 << ": " << get<1>(vExact.at(j))->getId() << endl;

            outputFile << distanceOutput(isLsh) << get<0>(vAppr.at(j - diff)) << endl;
            outputFile << "distanceTrue: " << get<0>(vExact.at(j)) << endl << endl;
        }
        else {
            outputFile << "Approximate Nearest neighbour-"<< vExact.size() - j
                 << ": NOT FOUND" << endl;
            outputFile << "Exact Nearest neighbour-"<< vExact.size() - j
                 << ": " << get<1>(vExact.at(j))->getId() << endl;

            outputFile << distanceOutput(isLsh) << "-"<< endl;
            outputFile << "distanceTrue: " << get<0>(vExact.at(j)) << endl << endl;
        }

    }
    string timeMessg = isLsh ? "tLSH: " : "tHypercube: ";
    outputFile << timeMessg << get<1>(apprNearestImages).count() / 1e6 << "s" << endl;
    outputFile << "tTrue: " << get<1>(exactNearestImages).count() / 1e6 << "s" << endl << endl;

    printRangeNrstImages(apprRangeSrchImages, outputFile);
}

void unmarkImgs(vector<Image*> * imgs, int imgNum) {
    for (int i = 0; i < imgNum; ++i)
        imgs->at(i)->unmarkImage();
}

void unassignImgs(vector<Image*> * imgs, int imgNum) {
    for (int i = 0; i < imgNum; ++i)
        imgs->at(i)->unassignImageFromClst();
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
        getNearbyVertices(vec, currentVertex, (int)currentVertex.length() - 1, curDist);
}