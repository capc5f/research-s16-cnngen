//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "LRNLayer.h"

LRNLayer::LRNLayer(std::string name) {
    setName(name);
    setType(LRN);
    mLocalSize = 5;
    mAlpha = 1;
    mBeta = 5;
}

LRNLayer::LRNLayer(std::string name, int local_size, float alpha, float beta, NormRegion norm_region) {
    setName(name);
    setType(LRN);
    setLocalSize(local_size);
    setAlpha(alpha);
    setBeta(beta);
    setNormRegion(norm_region);
}

LRNLayer::~LRNLayer() {

}

int LRNLayer::getLocalSize() {
    return this->mLocalSize;
}

void LRNLayer::setLocalSize(int local_size) {
    this->mLocalSize = local_size;
}

float LRNLayer::getAlpha() {
    return this->mAlpha;
}

void LRNLayer::setAlpha(float alpha) {
    this->mAlpha = alpha;
}

float LRNLayer::getBeta() {
    return this->mBeta;
}

void LRNLayer::setBeta(float beta) {
    this->mBeta = beta;
}

std::string LRNLayer::getNormRegion() {
    switch ( mNormRegion ) {
        case ACROSS_CHANNELS:
            return "ACROSS_CHANNELS";

        case WITHIN_CHANNEL:
            return "WITHIN_CHANNEL";

        default:
            return "ACROSS_CHANNELS";
    }
}

void LRNLayer::setNormRegion(NormRegion norm_region) {
    this->mNormRegion = norm_region;
}

std::string LRNLayer::toString() {
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

    ss << "  lrn_param {\n";
    ss << "    local_size: " << getLocalSize() << "\n";
    ss << "    alpha: " << getAlpha() << "\n";
    ss << "    beta: " << getBeta() << "\n";
    ss << "    norm_region: ";
    ss << getNormRegion() << "\n";
    ss << "  }\n";
    ss << "}" << std::endl;

    return ss.str();
}
