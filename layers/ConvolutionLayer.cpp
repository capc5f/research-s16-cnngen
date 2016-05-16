//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "ConvolutionLayer.h"

ConvolutionLayer::ConvolutionLayer(std::string name) {
    setType(CONVOLUTION);
    setName(name);
    mPadding = 0;
    mStride = 1;
    mHasWeightFiller = false;
    mHasBiasFiller = false;
    mHasPadding = false;
}

ConvolutionLayer::ConvolutionLayer(std::string name, int depth, int filter_size, int stride) {
    setType(CONVOLUTION);
    setName(name);
    setDepth(depth);
    setFilterSize(filter_size);
    setStride(stride);
    mPadding = 0;
    mHasWeightFiller = false;
    mHasBiasFiller = false;
    mHasPadding = false;
}

ConvolutionLayer::ConvolutionLayer(std::string name, int depth, int pad, int filter_size, int stride) {
    setType(CONVOLUTION);
    setName(name);
    setDepth(depth);
    setPadding(pad);
    setFilterSize(filter_size);
    setStride(stride);
    mHasWeightFiller = false;
    mHasBiasFiller = false;
}

ConvolutionLayer::ConvolutionLayer(std::string name, int depth, int filter_size, int stride, WeightFiller weight_filler, BiasFiller bias_filler) {

}

ConvolutionLayer::ConvolutionLayer(std::string name, int depth, int pad, int filter_size, int stride, int num_gen_param) {
    setType(CONVOLUTION);
    setName(name);
    setDepth(depth);
    setPadding(pad);
    setFilterSize(filter_size);
    setStride(stride);
    mHasWeightFiller = false;
    mHasBiasFiller = false;
//    mGenParams.resize(num_gen_param);
}

ConvolutionLayer::~ConvolutionLayer() {

}

std::string ConvolutionLayer::toString() {
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
            ss << "  }" << std::endl;
        }
    }

    ss << "  convolution_param {" << std::endl;
    ss << "    num_output: " << getDepth() << std::endl;

    if ( hasPadding() )
        ss << "    pad: " << getPadding() << std::endl;

    ss << "    kernel_size: " << getFilterSize() << std::endl;
    ss << "    stride: " << getStride() << std::endl;

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

int ConvolutionLayer::getDepth() {
    return this->mDepth;
}

void ConvolutionLayer::setDepth(int depth) {
    this->mDepth = depth;
}

bool ConvolutionLayer::hasPadding() {
    return this->mHasPadding;
}

int ConvolutionLayer::getPadding() {
    return this->mPadding;
}

void ConvolutionLayer::setPadding(int pad) {
    this->mHasPadding = true;
    this->mPadding = pad;
}

int ConvolutionLayer::getFilterSize() {
    return this->mFilterSize;
}

void ConvolutionLayer::setFilterSize(int filter_size) {
    this->mFilterSize = filter_size;
}

int ConvolutionLayer::getStride() {
    return this->mStride;
}

void ConvolutionLayer::setStride(int stride) {
    this->mStride = stride;
}

void ConvolutionLayer::setParamAtIndex(int index, int lr_mult, int decay_mult) {
    Param *p = new Param(lr_mult, decay_mult);
    mGenParams.push_back(*p);
}

Param ConvolutionLayer::getParamAtIndex(int index) {
    return this->mGenParams.at(index);
}

bool ConvolutionLayer::hasWeightFiller() {
    return this->mHasWeightFiller;
}

std::string ConvolutionLayer::getWeightFiller() {
    switch ( mWeightFiller ) {
        case XAVIER:
            return "xavier";

        case GAUSSIAN:
            return "gaussian";

        default:
            return "";
    }
}

void ConvolutionLayer::setWeightFiller(WeightFiller weight_filler) {
    this->mHasWeightFiller = true;
    this->mWeightFiller = weight_filler;
}

bool ConvolutionLayer::hasBiasFiller() {
    return this->mHasBiasFiller;
}

std::string ConvolutionLayer::getBiasFiller() {
    switch ( mBiasFiller ) {
        case CONSTANT:
            return "constant";

        default:
            return "constant";
    }
}

void ConvolutionLayer::setBiasFiller(BiasFiller bias_filler) {
    this->mHasBiasFiller = true;
    this->mBiasFiller = bias_filler;
}
