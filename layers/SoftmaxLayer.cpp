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

    ss << "layer {\n";
    ss << "  name: \"";
    ss << getName() << "\"\n";
    ss << "  type: \"";
    ss << getType() << "\"\n";

    if ( hasBottom() ) {
        ss << "  bottom: \"";
        ss << getBottom() << "\"\n";
    }

    if ( hasTop() ) {
        ss << "  top: \"";
        ss << getTop() << "\"\n";
    }

    ss << "}" << std::endl;

    return ss.str();
}