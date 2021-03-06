//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_GENERATELAYERS_H
#define RESEARCHDNNGENERATOR_GENERATELAYERS_H

#include <sstream>
#include <vector>
#include <cstdlib>
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
    unsigned long mTotalLayers;
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
    ConvolutionLayer* buildConvolutionLayer(int in_width, int in_height, int f_size, int depth);
    PoolingLayer* buildPoolingLayer(int in_size, int filter_size, PoolingType type, int stride);
    PoolingLayer* buildPoolingLayerMax2by2(int in_size, int depth);
    ReLULayer* buildReLULayer(int in_size);
    ReLULayer* buildReLULayer(int width, int height, int depth);
    InnerProductLayer* buildInnerProductLayer(int in_size, int out_size);
    InnerProductLayer* buildInnerProductLayer(int in_width, int in_height, int out_width, int out_height);
    InnerProductLayer* buildInnerProductLayer(int in_width, int in_height, int in_depth, int out_width, int out_height, int out_depth);
    void setTopAndBottom();

    void setTotalLayers();

public:
    GenerateLayers(UserInput in);
    std::vector <LayerBase *> getLayerList();

    unsigned long getTotalNumberLayers();
};

int checkConvPadding(int filter_size);

#endif //RESEARCHDNNGENERATOR_GENERATELAYERS_H
