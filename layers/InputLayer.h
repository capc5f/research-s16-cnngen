//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_INPUTLAYER_H
#define RESEARCHDNNGENERATOR_INPUTLAYER_H


#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "LayerBase.h"

class InputLayer: public LayerBase {
private:
    int mNumberInput;
    int mWidth;
    int mHeight;
    int mNumChannels;

public:
    InputLayer(std::string name, int number_input, int channels, int height, int width);
    ~InputLayer();
    void init();
    int getNumberInput();
    int getHeight();
    int getWidth();
    int getNumChannels();
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_INPUTLAYER_H
