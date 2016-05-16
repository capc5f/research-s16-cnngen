//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_POOLINGLAYER_H
#define RESEARCHDNNGENERATOR_POOLINGLAYER_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "LayerBase.h"

enum PoolingType {
    MAX, AVERAGE, STOCHASTIC
};

class PoolingLayer: public LayerBase {
private:
    PoolingType mPoolingType;
    int mKernelSize;
    int mStride;
    int mPadding;
    bool mHasPadding;

public:
    PoolingLayer(std::string name);
    PoolingLayer(std::string name, PoolingType pool, int kernel_size, int stride);
    PoolingLayer(std::string name, PoolingType pool, int kernel_size, int stride, int pad);
    ~PoolingLayer();
    void init();
    bool hasPadding();
    int getPadding();
    void setPadding(int pad);
    int getKernelSize();
    void setKernelSize(int kernel_size);
    int getStride();
    void setStride(int stride);
    std::string getPoolingType();
    void setPoolingType(PoolingType pool);
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_POOLINGLAYER_H
