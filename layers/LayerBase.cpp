//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "LayerBase.h"

LayerBase::LayerBase() {
    mHasBottom = false;
    mHasTop = false;
}

LayerBase::LayerBase(std::string name, LayerType type) {
    mHasBottom = false;
    mHasTop = false;
    setName(name);
    setType(type);
}

LayerBase::~LayerBase() {

}

int LayerBase::getInputWidth() {
    return this->mInputWidth;
}

void LayerBase::setInputWidth(int input_width) {
    this->mInputWidth = input_width;
}

int LayerBase::getInputHeight() {
    return this->mInputHeight;
}

void LayerBase::setInputHeight(int input_height) {
    this->mInputHeight = input_height;
}

int LayerBase::getInputDepth() {
    return this->mInputDepth;
}

void LayerBase::setInputDepth(int input_depth) {
    this->mInputDepth = input_depth;
}

int LayerBase::getOutputWidth() {
    return this->mOutputWidth;
}

void LayerBase::setOutputWidth(int output_width) {
    this->mOutputWidth = output_width;
}

int LayerBase::getOutputHeight() {
    return this->mOutputHeight;
}

void LayerBase::setOutputHeight(int output_height) {
    this->mOutputHeight = output_height;
}

int LayerBase::getOutputDepth() {
    return this->mOutputDepth;
}

void LayerBase::setOutputDepth(int output_depth) {
    this->mOutputDepth = output_depth;
}

bool LayerBase::hasTop() {
    return this->mHasTop;
}

std::string LayerBase::getTop() {
    return this->mTop;
}

void LayerBase::setTop(std::string top) {
    if ( top.length() > 0 ) //todo: fix this to verify correctly, or store a reference to the top
        mHasTop = true;

    this->mTop = top;
}

bool LayerBase::hasBottom() {
    return this->mHasBottom;
}

std::string LayerBase::getBottom() {
    return this->mBottom;
}

void LayerBase::setBottom(std::string bottom) {
    if ( bottom.length() > 0 )
        mHasBottom = true;

    this->mBottom = bottom;
}

std::string LayerBase::getName() {
    return mName;
}

void LayerBase::setName(std::string name) {
    this->mName = name;
}

std::string LayerBase::getType() {
    switch ( this->mType ) {
        case INPUT:
            return "Input";
        case CONVOLUTION:
            return "Convolution";
        case POOLING:
            return "Pooling";
        case RELU:
            return "ReLU";
        case LRN:
            return "LRN";
        case INNER_PRODUCT:
            return "Inner Product";
        case SOFTMAX:
            return "Softmax";
        default:
            return "";
    }
}

void LayerBase::setType(LayerType type) {
    this->mType = type;
}

LayerType LayerBase::getLayerType() {
    return this->mType;
}

std::string LayerBase::toString() {
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
    ss << "}" << std::endl;

    return ss.str();
}
