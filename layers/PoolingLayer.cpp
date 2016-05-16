//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "PoolingLayer.h"

PoolingLayer::PoolingLayer(std::string name): LayerBase(name, POOLING) {
    init();
}

PoolingLayer::PoolingLayer(std::string name, PoolingType pool, int filter_size, int stride): LayerBase(name, POOLING) {
    init();
    setPoolingType(pool);
    setKernelSize(filter_size);
    setStride(stride);
}

PoolingLayer::PoolingLayer(std::string name, PoolingType pool, int filter_size, int stride, int pad): LayerBase(name, POOLING) {
    init();
    setPoolingType(pool);
    setKernelSize(filter_size);
    setStride(stride);
    setPadding(pad);
    this->mHasPadding = true;
}

PoolingLayer::~PoolingLayer() {

}

void PoolingLayer::init() {
    mStride = 1;
    mPadding = 0;
    mHasPadding = false;
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

    ss << "  pooling_param {\n";
    ss << "    pool: ";
    ss << getPoolingType() << "\n";

    if ( hasPadding() )
        ss << "    pad: " << getPadding() << "\n";

    ss << "    kernel_size: " << getKernelSize() << "\n";
    ss << "    stride: " << getStride() << "\n";
    ss << "  }\n";
    ss << "}" << std::endl;

    return ss.str();
}
