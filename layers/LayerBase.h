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
    int mInputWidth;
    int mInputHeight;
    int mInputDepth;
    int mOutputWidth;
    int mOutputHeight;
    int mOutputDepth;
//    LayerCategory mLayerCat; // todo: FUTUREWORK -- switch from LayerType enum to this

public:
    LayerBase(std::string name, LayerType type);
    ~LayerBase();
    virtual void init();
    int getInputWidth();
    void setInputWidth(int input_width);
    int getInputHeight();
    void setInputHeight(int input_height);
    int getInputDepth();
    void setInputDepth(int input_depth);
    int getOutputWidth();
    void setOutputWidth(int output_width);
    int getOutputHeight();
    void setOutputHeight(int output_height);
    int getOutputDepth();
    void setOutputDepth(int output_depth);
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
