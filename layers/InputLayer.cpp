//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "InputLayer.h"

InputLayer::InputLayer(std::string name, int num, int channels, int height, int width) {
    setName(name);
    setType(INPUT);
    std::vector<int> shape(4);
    shape[0] = num;
    shape[1] = channels;
    shape[2] = height;
    shape[3] = width;
    mShape = shape;
}

std::string InputLayer::toString() {
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

    ss << "  input_param { shape: { ";
    for (int i = 0; i < mShape.size(); ++i) {
        ss << "dim: " << mShape.at(i) << " ";
    }
    ss << "} }\n";
    ss << "}" << std::endl;

    return ss.str();
}