//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_CONVOLUTIONLAYER_H
#define RESEARCHDNNGENERATOR_CONVOLUTIONLAYER_H


#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "LayerBase.h"
#include "layer_helpers/Param.h"

class ConvolutionLayer: public LayerBase {
private:
    std::vector <Param> mGenParams;
    int mPadding;
    int mFilterSize;
    int mStride;
    WeightFiller mWeightFiller;
    BiasFiller mBiasFiller;
    bool mHasWeightFiller;
    bool mHasBiasFiller;
    bool mHasPadding;

public:
    ConvolutionLayer(std::string name);
    ConvolutionLayer(std::string name, int depth, int kernel_size, int stride);
    ConvolutionLayer(std::string name, int depth, int pad, int kernel_size, int stride);
    ConvolutionLayer(std::string name, int depth, int kernel_size, int stride, WeightFiller weight_filler, BiasFiller bias_filler);
    ConvolutionLayer(std::string name, int depth, int pad, int kernel_size, int stride, int num_gen_param);
    ~ConvolutionLayer();
    bool hasPadding();
    int getPadding();
    void setPadding(int pad);
    int getFilterSize();
    void setFilterSize(int filter_size);
    int getStride();
    void setStride(int stride);
    void setParamAtIndex(int index, int lr_mult, int decay_mult);
    Param getParamAtIndex(int index);
    bool hasWeightFiller();
    void setHasWeightFiller(bool state);
    std::string getWeightFiller();
    void setWeightFiller(WeightFiller weight_filler);
    bool hasBiasFiller();
    std::string getBiasFiller();
    void setBiasFiller(BiasFiller bias_filler);
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_CONVOLUTIONLAYER_H
