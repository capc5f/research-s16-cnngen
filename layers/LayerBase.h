//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_LAYERBASE_H
#define RESEARCHDNNGENERATOR_LAYERBASE_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "layer_helpers/LayerEnums.h"
#include "layer_helpers/LayerTypes.h"

class LayerBase {
protected:
    std::string mName;
    LayerType mType;
    std::string mBottom;
    std::string mTop;
    bool mHasTop;
    bool mHasBottom;
    int mWidth;
    int mHeight;
//    LayerCategory mLayerCat; // todo: FUTUREWORK -- switch from LayerType enum to this

public:
    LayerBase();
    LayerBase(std::string name, LayerType type);
    ~LayerBase();
    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
    bool hasTop();
    std::string getTop();
    void setTop(std::string top);
    bool hasBottom();
    std::string getBottom();
    void setBottom(std::string bottom);
    std::string getName();
    void setName(std::string name);
    std::string getType();
    void setType(LayerType type);
    LayerType getLayerType();
    virtual std::string toString();
};


#endif //RESEARCHDNNGENERATOR_LAYERBASE_H
