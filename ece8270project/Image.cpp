//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "Image.h"

Image::Image(int num_channels, int width, int height) {
    setWidth(width);
    setHeight(height);
    setNumChannels(num_channels);
}

Image::~Image() {
    delete mData;
}

int Image::getNumChannels() {
    return this->mNumChannels;
}

void Image::setNumChannels(int num_channels) {
    this->mNumChannels = num_channels;
    int size = mNumChannels * mHeight * mWidth;
    mData = new std::vector<uint8_t>(size);
}

int Image::getWidth() {
    return this->mWidth;
}

void Image::setWidth(int width) {
    this->mWidth = width;
}

int Image::getHeight() {
    return this->mHeight;
}

void Image::setHeight(int height) {
    this->mHeight = height;
}

std::string Image::toString() {
    std::stringstream ss;

    return ss.str();
}