//
// Created by Cody Price on 5/12/16.
//

#ifndef RESEARCHDNNGENERATOR_INNERPRODUCTLAYER_H
#define RESEARCHDNNGENERATOR_INNERPRODUCTLAYER_H


#include <string>
#include <vector>
#include <sstream>

#include "LayerBase.h"
#include "layer_helpers/Param.h"

class InnerProductLayer: public LayerBase {
private:
    std::vector <Param> mGenParams;
    int mWidth;
    int mHeight;
    int mNumOutput;
    WeightFiller mWeightFiller;
    BiasFiller mBiasFiller;
    bool mHasWeightFiller;
    bool mHasBiasFiller;

public:
    InnerProductLayer(std::string name);
    InnerProductLayer(std::string name, int num_output);
    ~InnerProductLayer();
    int getNumOutput();
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
