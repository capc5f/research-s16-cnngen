//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "PoolingLayer.h"

PoolingLayer::PoolingLayer(std::string name) {
    setType(POOLING);
    setName(name);
}

PoolingLayer::PoolingLayer(std::string name, PoolingType pool, int kernel_size, int stride) {
    setName(name);
    setType(POOLING);
    setPoolingType(pool);
    setKernelSize(kernel_size);
    setStride(stride);
}

PoolingLayer::PoolingLayer(std::string name, PoolingType pool, int kernel_size, int stride, int pad) {
    setName(name);
    setType(POOLING);
    setPoolingType(pool);
    setKernelSize(kernel_size);
    setStride(stride);
    setPadding(pad);
    this->mHasPadding = true;
}

PoolingLayer::~PoolingLayer() {

}

bool PoolingLayer::hasPadding() {
    return this->mHasPadding;
}

int PoolingLayer::getPadding() {
    return this->mPadding;
}

void PoolingLayer::setPadding(int pad) {
    this->mPadding = pad;
    this->mHasPadding = true;
}

int PoolingLayer::getKernelSize() {
    return this->mKernelSize;
}

void PoolingLayer::setKernelSize(int kernel_size) {
    this->mKernelSize = kernel_size;
}

int PoolingLayer::getStride() {
    return this->mStride;
}

void PoolingLayer::setStride(int stride) {
    this->mStride = stride;
}

std::string PoolingLayer::getPoolingType() {
    switch ( mPoolingType ) {
        case MAX:
            return "MAX";

        case AVERAGE:
            return "AVE";

        case STOCHASTIC:
            return "STOCHASTIC";

        default:
            return "MAX";
    }
}

void PoolingLayer::setPoolingType(PoolingType pool) {
    this->mPoolingType = pool;
}

std::string PoolingLayer::toString() {
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

    ss << "  pooling_param {" << std::endl;
    ss << "    pool: ";
    ss << getPoolingType() << std::endl;

    if ( hasPadding() )
        ss << "    pad: " << getPadding() << std::endl;

    ss << "    kernel_size: " << getKernelSize() << std::endl;
    ss << "    stride: " << getStride() << std::endl;
    ss << "  }" << std::endl;
    ss << "}" << std::endl;

    return ss.str();
}
