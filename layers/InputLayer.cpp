//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "InputLayer.h"

InputLayer::InputLayer(std::string name, int number_input, int channels, int height, int width): LayerBase(name, INPUT) {
    this->mNumberInput = number_input;
    this->mNumChannels = channels;
    this->mHeight = height;
    this->mWidth = width;
    init();
}

void InputLayer::init() {
    setInputWidth(mWidth);
    setOutputWidth(mWidth);
    setInputHeight(mHeight);
    setOutputHeight(mHeight);
    setInputDepth(mNumChannels);
    setOutputDepth(mNumChannels);
}

int InputLayer::getNumberInput() {
    return this->mNumberInput;
}

int InputLayer::getHeight() {
    return this->mHeight;
}

int InputLayer::getWidth() {
    return this->mWidth;
}

int InputLayer::getNumChannels() {
    return this->mNumChannels;
}

std::string InputLayer::toString() {
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

    ss << "  input_param { shape: { ";
    ss << "dim: " << mNumberInput << " ";
    ss << "dim: " << mNumChannels << " ";
    ss << "dim: " << mHeight << " ";
    ss << "dim: " << mWidth << " ";
    ss << "} }\n";
    ss << "}" << std::endl;

    return ss.str();
}