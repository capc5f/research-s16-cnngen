//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_INNERPRODUCTLAYER_H
#define RESEARCHDNNGENERATOR_INNERPRODUCTLAYER_H


#include <string>
#include <vector>
#include <sstream>

#include "LayerBase.h"
#include "layer_helpers/Param.h"
#include "ConvolutionLayer.h"

class InnerProductLayer: public LayerBase {
private:
    std::vector <Param> mGenParams;
    int mNumOutput;
    WeightFiller mWeightFiller;
    BiasFiller mBiasFiller;
    bool mHasWeightFiller;
    bool mHasBiasFiller;
    float mAlpha;
    float mBeta;

public:
    InnerProductLayer(std::string name);
    InnerProductLayer(std::string name, int num_output);
    InnerProductLayer(std::string name, int in_width, int in_height, int out_width, int out_height);
    ~InnerProductLayer();
    void init();
    int getNumOutput();
    const void* getAlpha();
    void setAlpha(float alpha);
    const void* getBeta();
    void setBeta(float beta);
    void setNumOutput(int num_output);
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


#endif //RESEARCHDNNGENERATOR_INNERPRODUCTLAYER_H
