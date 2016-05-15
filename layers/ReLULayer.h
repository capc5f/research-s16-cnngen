//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_RELULAYER_H
#define RESEARCHDNNGENERATOR_RELULAYER_H


#include <string>
#include <sstream>

#include "LayerBase.h"

class ReLULayer: public LayerBase {
private:

public:
    ReLULayer(std::string name);
    ~ReLULayer();
};


#endif //RESEARCHDNNGENERATOR_RELULAYER_H
