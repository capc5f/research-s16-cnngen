//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "Image.h"

Image::Image(int num_channels, int width, int height) {
    init();

    setWidth(width);
    setHeight(height);
    setNumChannels(num_channels);
}

Image::Image(int num_channels, int width, int height, int classification) {
    init();

    setWidth(width);
    setHeight(height);
    setNumChannels(num_channels);
    setClassification(classification);
}

Image::~Image() {
    delete[] mData;
}

void Image::init() {
    setImageType(CIFAR10); // todo: FUTUREWORK -- allow for different imagesets
    mClassification = -1;
}

void Image::setClassification(int classification) {
    this->mClassification = classification;
}

void Image::setNumChannels(int num_channels) {
    this->mNumChannels = num_channels;
    mSize = mNumChannels * mHeight * mWidth;
    mData = new uint8_t[mSize];
}

void Image::setWidth(int width) {
    this->mWidth = width;
}

void Image::setHeight(int height) {
    this->mHeight = height;
}

void Image::setImageType(ImageType image_type) {
    this->mImageType = image_type;
}

std::string Image::getClassification() {
    switch ( mClassification ) {
        case 0: return "airplane";

        case 1: return "automobile";

        case 2: return "bird";

        case 3: return "cat";

        case 4: return "deer";

        case 5: return "dog";

        case 6: return "frog";

        case 7: return "horse";

        case 8: return "ship";

        case 9: return "truck";

        default: return "??";
    }
}

int Image::getNumChannels() {
    return this->mNumChannels;
}

int Image::getWidth() {
    return this->mWidth;
}

int Image::getHeight() {
    return this->mHeight;
}

std::string Image::getImageType() {
    switch ( mImageType ) {
        case CIFAR10:
            return "Cifar-10";

        case UNSUPPORTED:
        default:
            return "Unsupported dataset";
    }
}

uint8_t* Image::getData() {
    return mData;
}

std::string Image::toString() {
    std::stringstream ss;

    ss << "Image\nType: ";
    ss <<  getImageType() << "\n";
    ss << "Classification: (" << mClassification << ") ";
    ss << getClassification() << "\n";
    ss << "Width = " << mWidth << "\n";
    ss << "Height = " << mHeight << "\n";
    ss << "Number of channels = " << mNumChannels << std::endl;

    return ss.str();
}

