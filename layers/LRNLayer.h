//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_LRNLAYER_H
#define RESEARCHDNNGENERATOR_LRNLAYER_H


#include <string>
#include <vector>
#include <sstream>

#include "LayerBase.h"

enum NormRegion {
    ACROSS_CHANNELS, WITHIN_CHANNEL
};

class LRNLayer: public LayerBase {
private:
    int mLocalSize;
    float mAlpha;
    float mBeta;
    NormRegion mNormRegion;

public:
    LRNLayer(std::string name);
    LRNLayer(std::string name, int local_size, float alpha, float beta, NormRegion norm_region);
    ~LRNLayer();
    void init();
    int getLocalSize();
    void setLocalSize(int local_size);
    float getAlpha();
    void setAlpha(float alpha);
    float getBeta();
    void setBeta(float beta);
    std::string getNormRegion();
    void setNormRegion(NormRegion norm_region);
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_LRNLAYER_H
