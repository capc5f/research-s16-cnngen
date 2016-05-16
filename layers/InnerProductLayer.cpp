//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "InnerProductLayer.h"

InnerProductLayer::InnerProductLayer(std::string name) {
    setName(name);
    setType(INNER_PRODUCT);
    mHasWeightFiller = false;
    mHasBiasFiller = false;
}

InnerProductLayer::InnerProductLayer(std::string name, int num_output) {
    setName(name);
    setType(INNER_PRODUCT);
    setNumOutput(num_output);
    mHasWeightFiller = false;
    mHasBiasFiller = false;
}

InnerProductLayer::~InnerProductLayer() {

}

std::string InnerProductLayer::toString() {
    std::stringstream ss;

    ss << "layer {" << std::endl;
    ss << "  name: \"";
    ss << getName() << "\"" << std::endl;
    ss << "  type: \"";
    ss << getType() << "\"" << std::endl;

    if ( hasBottom() ) {
        ss << "  bottom: \"";
        ss << getBottom() << "\"" << std::endl;
    }

    if ( hasTop() ) {
        ss << "  top: \"";
        ss << getTop() << "\"" << std::endl;
    }

    if ( mGenParams.size() > 0 ) {
        for (int i = 0; i < mGenParams.size(); ++i) {
            ss << "  param {" << std::endl;
            ss << "    lr_mult: " << mGenParams.at(i).getLearningRate() << std::endl;
            ss << "    decay_mult: " << mGenParams.at(i).getDecayMult() << std::endl;
            ss << "  }" << std::endl;
        }
    }

    ss << "  inner_product_param {" << std::endl;
    ss << "    num_output: " << getNumOutput() << std::endl;

    if ( hasWeightFiller() ) {
        ss << "    weight_filler {" << std::endl;
        ss << "      type: \"";
        ss << getWeightFiller() << "\"" << std::endl;
        ss << "    }" << std::endl;
    }

    if ( hasBiasFiller() ) {
        ss << "    bias_filler {" << std::endl;
        ss << "      type: \"";
        ss << getBiasFiller() << "\"" << std::endl;
        ss << "    }" << std::endl;
    }

    ss << "  }" << std::endl;
    ss << "}" << std::endl;

    return ss.str();
}

int InnerProductLayer::getNumOutput() {
    return this->mNumOutput;
}

void InnerProductLayer::setNumOutput(int num_output) {
    this->mNumOutput = num_output;
}

void InnerProductLayer::setParamAtIndex(int index, int lr_mult, int decay_mult) {
    Param *p = new Param(lr_mult, decay_mult);
    mGenParams.push_back(*p);
}

Param InnerProductLayer::getParamAtIndex(int index) {
    return this->mGenParams.at(index);
}

bool InnerProductLayer::hasWeightFiller() {
    return this->mHasWeightFiller;
}

std::string InnerProductLayer::getWeightFiller() {
    switch ( mWeightFiller ) {
        case XAVIER:
            return "xavier";

        case GAUSSIAN:
            return "gaussian";

        default:
            return "";
    }
}

void InnerProductLayer::setWeightFiller(WeightFiller weight_filler) {
    this->mHasWeightFiller = true;
    this->mWeightFiller = weight_filler;
}

bool InnerProductLayer::hasBiasFiller() {
    return this->mHasBiasFiller;
}

std::string InnerProductLayer::getBiasFiller() {
    switch ( mBiasFiller ) {
        case CONSTANT:
            return "constant";

        default:
            return "constant";
    }
}

void InnerProductLayer::setBiasFiller(BiasFiller bias_filler) {
    this->mHasBiasFiller = true;
    this->mBiasFiller = bias_filler;
}
