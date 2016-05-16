//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "InnerProductLayer.h"

InnerProductLayer::InnerProductLayer(std::string name): LayerBase(name, INNER_PRODUCT) {
    init();
}

InnerProductLayer::InnerProductLayer(std::string name, int num_output): LayerBase(name, INNER_PRODUCT) {
    init();
    setNumOutput(num_output);
}

InnerProductLayer::InnerProductLayer(std::string name, int in_width, int in_height, int out_width, int out_height): LayerBase(name, INNER_PRODUCT) {
    init();
    setNumOutput(out_height);
    setInputWidth(in_width);
    setInputHeight(in_height);
    setOutputWidth(out_width);
    setOutputHeight(out_height);
}

InnerProductLayer::~InnerProductLayer() {

}

void InnerProductLayer::init() {
    mAlpha = 0.0;
    mBeta = 0.0;
    mHasWeightFiller = false;
    mHasBiasFiller = false;
    setOutputDepth(1);
}

const void* InnerProductLayer::getAlpha() {
    const void* a = &mAlpha;
    return a;
}

void InnerProductLayer::setAlpha(float alpha) {
    this->mAlpha = alpha;
}

const void* InnerProductLayer::getBeta() {
    const void* b = &mBeta;
    return b;
}

void InnerProductLayer::setBeta(float beta) {
    this->mBeta = beta;
}

std::string InnerProductLayer::toString() {
    std::stringstream ss;

    ss << "layer {\n";
    ss << "  name: \"";
    ss << getName() << "\"\n";
    ss << "  type: \"";
    ss << getType() << "\"\n";

    if ( hasBottom() ) {
        ss << "  bottom: \"";
        ss << getBottom() << "\"\n";
    }

    if ( hasTop() ) {
        ss << "  top: \"";
        ss << getTop() << "\"\n";
    }

    if ( mGenParams.size() > 0 ) {
        for (int i = 0; i < mGenParams.size(); ++i) {
            ss << "  param {\n";
            ss << "    lr_mult: " << mGenParams.at(i).getLearningRate() << "\n";
            ss << "    decay_mult: " << mGenParams.at(i).getDecayMult() << "\n";
            ss << "  }\n";
        }
    }

    ss << "  inner_product_param {" << "\n";
    ss << "    num_output: " << getNumOutput() << "\n";

    if ( hasWeightFiller() ) {
        ss << "    weight_filler {\n";
        ss << "      type: \"";
        ss << getWeightFiller() << "\"\n";
        ss << "    }\n";
    }

    if ( hasBiasFiller() ) {
        ss << "    bias_filler {\n";
        ss << "      type: \"";
        ss << getBiasFiller() << "\"\n";
        ss << "    }\n";
    }

    ss << "  }\n";
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
