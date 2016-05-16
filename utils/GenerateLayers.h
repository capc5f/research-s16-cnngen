//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_GENERATELAYERS_H
#define RESEARCHDNNGENERATOR_GENERATELAYERS_H

#include <sstream>
#include <vector>
#include <random>

#include "UserInput.h"
#include "NetworkMode.h"
#include "../layers/LayerBase.h"
#include "../layers/InputLayer.h"
#include "../layers/ConvolutionLayer.h"
#include "../layers/PoolingLayer.h"
#include "../layers/ReLULayer.h"
#include "../layers/InnerProductLayer.h"

class GenerateLayers {
private:
    std::vector <LayerBase *> mLayerList;
    int mTotalLayers;
    int mNumberInput;
    int mInputWidth;
    int mInputHeight;
    int mNumInputChannels;
    int mNumConvLayers;
    int mConvFilterSize;
    int mNumFullyConnLayers;
    int mOutputDim;
    NetworkMode mNetworkMode;
    double mThreshold;
    int mNumConvUsed;
    int mNumPoolUsed;
    int mNumReluUsed;
    int mNumFullyConnUsed;

    void init();
    void buildLayerList();
    InputLayer* buildInputLayer();
    ConvolutionLayer* buildConvolutionLayer(int in_size, int f_size, int depth);
    PoolingLayer* buildPoolingLayer(int in_size, int filter_size, PoolingType type, int stride);
    PoolingLayer* buildPoolingLayerMax2by2(int in_size);
    ReLULayer* buildReLULayer(int in_size);
    InnerProductLayer* buildInnerProductLayer(int in_size, int out_size);
    InnerProductLayer* buildInnerProductLayer(int in_width, int in_height, int out_width, int out_height);

public:
    GenerateLayers(UserInput in);
    std::vector <LayerBase *> getLayerList();
};

int checkConvPadding(int filter_size);

#endif //RESEARCHDNNGENERATOR_GENERATELAYERS_H
