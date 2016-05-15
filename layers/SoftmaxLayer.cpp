//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "SoftmaxLayer.h"

SoftMaxLayer::SoftMaxLayer(std::string name) {
    setName(name);
    setType(SOFTMAX);
}

SoftMaxLayer::~SoftMaxLayer() {

}

std::string SoftMaxLayer::toString() {
    std::stringstream ss;

    ss << "layer {" << std::endl;
    ss << "  name: \"";
    ss << getName() << "\"" << std::endl;
    ss << "  type: \"";
    ss << getType() << "\"" << std::endl;

    if ( hasBottom() ) {
        ss << "  bottom: \"";
        ss << getBottom() << "\"" << std::endl;
    }

    if ( hasTop() ) {
        ss << "  top: \"";
        ss << getTop() << "\"" << std::endl;
    }

    ss << "}" << std::endl;

    return ss.str();
}