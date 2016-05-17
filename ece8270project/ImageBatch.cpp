//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "ImageBatch.h"

int ImageBatch::sNumberOfBatches = 0;

int ImageBatch::totalNumBatches() {
    return sNumberOfBatches;
}

ImageBatch::ImageBatch(int length, uint8_t* data) {
    init();
    this->mLength = length;
    this->mData = data;
}

ImageBatch::~ImageBatch() {
    delete[] mBatch;
    --sNumberOfBatches;
}

void ImageBatch::init() {
    mBatch = NULL;
    this->mBatchId = ++sNumberOfBatches;
}

float* ImageBatch::get() {
    convert();
    return this->mBatch;
}

void ImageBatch::convert() {
    mBatch = new float[mLength];
    for ( int i = 0; i < mLength; ++i ) {
        mBatch[i] = mData[i];
    }
}

void ImageBatch::clean() {
    delete[] mBatch;
    mBatch = NULL;
}

int ImageBatch::length() {
    return this->mLength;
}

int ImageBatch::getBatchId() {
    return this->mBatchId;
}
