#include "UtilsCluster.h"

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

double minDistance(Image * img, vector<Image *> *centroids) {
    double minDistance = numeric_limits<double>::infinity();
    for (Image * centroid : *centroids) {
        int newDist = manhattanDistance(img->getPixels(), centroid->getPixels());
        if(minDistance > newDist)
            minDistance = newDist;
    }
    return minDistance;
}

vector<double> calcMinDistances(vector<Image *> *imgs, vector<Image *> *centroids) {
    vector<double> toRet;
    toRet.push_back(0.0); // P(0) = 0
    for(Image * img: *imgs) {
        toRet.push_back(minDistance(img,centroids));
    }
    return toRet;
}

void normalizeDistances(vector<double> * distances) {
    double maxDist = *max_element(distances->begin(), distances->end());
    for (double &dist: *distances) {
        dist /= maxDist;
    }
}

vector<double> getPropabilities(vector<Image *> *centroids, vector<Image *> *imgs) {
    vector<double> toRet = calcMinDistances(imgs, centroids);
    normalizeDistances(&toRet);
    for (int i = 1; i < toRet.size(); ++i) {
        toRet.at(i) = pow(toRet.at(i),2) + toRet.at(i-1);
    }
    return toRet;
}

int binSearch(const vector<double> &probs, int start, int end, const double &val) {
    if(start == end) { // reached last element of tree path
        if(val <= probs.at(start)) { // the last element is P(r)
            return start;
        }
        else if(val > probs.at(start)) { // the last element is P(r-1)
            return start + 1;
        }
    }

    if(start > end) { // P(r) is on the right
        return start;
    }

    int midl = floor((start + end) / 2);
    if(val > probs.at(midl)) // P(r) is in the right subtree
        return binSearch(probs, midl+1, end, val);
    else if(val < probs.at(midl)) // x is in the left subtree
        return binSearch(probs, start, midl-1, val);
    else // current element is P(r)
        return midl;
}


vector<Image *> kMeansPPlus(vector<Image *> imgs, int numOfCentroids) {
    unsigned seed = system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, imgs.size()-1);

    int index = distribution(generator);

    vector<Image *> centroids;
    centroids.push_back(imgs.at(index));
    vector<Image*>::iterator it = imgs.begin();
    imgs.erase(it + index);

    for(int i = 1; i < numOfCentroids; ++i) {
        vector<double> probs = getPropabilities(&centroids, &imgs);

        uniform_real_distribution<double> dist(0 + numeric_limits<double>::min(), probs.at(probs.size() - 1) + numeric_limits<double>::min());
        double rand_num = distribution(generator);

        std::vector<double>::iterator up;
        up= std::upper_bound (probs.begin(), probs.end(), rand_num);
        index = std::distance(probs.begin(), up);
        if(index == probs.size())
            index -= 1;
        centroids.push_back(imgs.at(index));
        it = imgs.begin();
        imgs.erase(it + index);
    }

    return centroids;
}