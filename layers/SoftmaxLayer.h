//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_SOFTMAXLAYER_H
#define RESEARCHDNNGENERATOR_SOFTMAXLAYER_H


#include <string>
#include <sstream>

#include "LayerBase.h"

class SoftMaxLayer: public LayerBase {
private:
public:
    SoftMaxLayer(std::string name);
    ~SoftMaxLayer();
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_SOFTMAXLAYER_H
