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
    std::vector <int> mShape;

public:
    InputLayer(std::string name, int num, int channels, int height, int width);
    ~InputLayer();
    int getHeight();
    int getWidth();
    int getNumChannels();
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_INPUTLAYER_H
