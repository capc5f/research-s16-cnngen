//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_IMAGE_H
#define RESEARCHDNNGENERATOR_IMAGE_H


#include <string>
#include <sstream>
#include <vector>

class Image {
private:
    int mNumChannels;
    int mWidth;
    int mHeight;
    std::vector<uint8_t> *mData;

public:
    Image(int num_channels, int width, int height);
    ~Image();
    int getNumChannels();
    void setNumChannels(int num_channels);
    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_IMAGE_H
