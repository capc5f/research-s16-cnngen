//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_IMAGE_H
#define RESEARCHDNNGENERATOR_IMAGE_H


#include <string>
#include <sstream>
#include <vector>

enum ImageType {
    CIFAR10, UNSUPPORTED
};

class Image {
private:
    int mClassification;
    int mNumChannels;
    int mWidth;
    int mHeight;
    ImageType mImageType;
    uint8_t *mData;
    int mSize;

    void init();
    void setClassification(int classification);
    void setNumChannels(int num_channels);
    void setHeight(int height);
    void setWidth(int width);
    void setImageType(ImageType image_type);

public:
    Image(int num_channels, int width, int height);
    Image(int num_channels, int width, int height, int classification);
    ~Image();
    std::string getClassification();
    int getNumChannels();
    int getWidth();
    int getHeight();
    std::string getImageType();
    uint8_t* getData();
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_IMAGE_H
