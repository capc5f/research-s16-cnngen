//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "LayerBase.h"

LayerBase::LayerBase() {

}

LayerBase::LayerBase(std::string name, LayerType type) {
    setName(name);
    setType(type);
}

LayerBase::~LayerBase() {

}

int LayerBase::getWidth() {
    return this->mWidth;
}

void LayerBase::setWidth(int width) {
    this->mWidth = width;
}

int LayerBase::getHeight() {
    return this->mHeight;
}

void LayerBase::setHeight(int height) {
    this->mHeight = height;
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
    ss << "}" << std::endl;

    return ss.str();
}
