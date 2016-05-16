//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "ConvolutionLayer.h"

ConvolutionLayer::ConvolutionLayer(std::string name) {
    setType(CONVOLUTION);
    setName(name);
    mPadding = 0;
    mStride = 1;
    mUpscaleX = 1;
    mUpscaleY = 1;
    mAlpha = 0.0;
    mBeta = 0.0;
    mHasWeightFiller = false;
    mHasBiasFiller = false;
    mHasPadding = false;
}

ConvolutionLayer::ConvolutionLayer(std::string name, int depth, int filter_size, int stride) {
    setType(CONVOLUTION);
    setName(name);
    setInputDepth(depth);
    setFilterDepth(depth);
    setOutputDepth(depth);
    setFilterSize(filter_size);
    setStride(stride);
    mPadding = 0;
    mUpscaleX = 1;
    mUpscaleY = 1;
    mAlpha = 0.0;
    mBeta = 0.0;
    mHasWeightFiller = false;
    mHasBiasFiller = false;
    mHasPadding = false;
}

ConvolutionLayer::ConvolutionLayer(std::string name, int depth, int pad, int filter_size, int stride) {
    setType(CONVOLUTION);
    setName(name);
    setInputDepth(depth);
    setFilterDepth(depth);
    setOutputDepth(depth);
    setPadding(pad);
    setFilterSize(filter_size);
    setStride(stride);
    mUpscaleX = 1;
    mUpscaleY = 1;
    mAlpha = 0.0;
    mBeta = 0.0;
    mHasWeightFiller = false;
    mHasBiasFiller = false;
}

// todo: does nothing right now.. has params for Caffe prototxt
ConvolutionLayer::ConvolutionLayer(std::string name, int depth, int filter_size, int stride, WeightFiller weight_filler, BiasFiller bias_filler) {

}

ConvolutionLayer::ConvolutionLayer(std::string name, int depth, int pad, int filter_size, int stride, int num_gen_param) {
    setType(CONVOLUTION);
    setName(name);
    setInputDepth(depth);
    setFilterDepth(depth);
    setOutputDepth(depth);
    setPadding(pad);
    setFilterSize(filter_size);
    setStride(stride);
    mUpscaleX = 1;
    mUpscaleY = 1;
    mAlpha = 0.0;
    mBeta = 0.0;
    mHasWeightFiller = false;
    mHasBiasFiller = false;
//    mGenParams.resize(num_gen_param);
}

ConvolutionLayer::~ConvolutionLayer() {

}

std::string ConvolutionLayer::toString() {
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
            ss << "  }\n";
        }
    }

    ss << "  convolution_param {\n";
    ss << "    num_output: " << getOutputDepth() << "\n";

    if ( hasPadding() )
        ss << "    pad: " << getPadding() << "\n";

    ss << "    kernel_size: " << getFilterSize() << "\n";
    ss << "    stride: " << getStride() << "\n";

    if ( hasWeightFiller() ) {
        ss << "    weight_filler {" << "\n";
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

int ConvolutionLayer::getFilterDepth() {
    return this->mFilterDepth;
}

void ConvolutionLayer::setFilterDepth(int filter_depth) {
    this->mFilterDepth = filter_depth;
}

int ConvolutionLayer::getStride() {
    return this->mStride;
}

void ConvolutionLayer::setStride(int stride) {
    this->mStride = stride;
}

int ConvolutionLayer::getUpscaleX() {
    return this->mUpscaleX;
}

int ConvolutionLayer::getUpscaleY() {
    return this->mUpscaleY;
}

const void* ConvolutionLayer::getAlpha() {
    const void* a = &mAlpha;
    return a;
}

void ConvolutionLayer::setAlpha(float alpha) {
    this->mAlpha = alpha;
}

const void* ConvolutionLayer::getBeta() {
    const void* b = &mBeta;
    return b;
}

void ConvolutionLayer::setBeta(float beta) {
    this->mBeta = beta;
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
