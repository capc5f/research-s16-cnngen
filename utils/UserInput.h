//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_USERINPUT_H
#define RESEARCHDNNGENERATOR_USERINPUT_H


#include <istream>
#include <fstream>
#include <iostream>
#include <string>
#include <strings.h>
#include <stdexcept>

#include "../layers/LayerBase.h"
#include "../layers/layer_helpers/LayerTypes.h"
#include "NetworkMode.h"

class UserInput {
private:
    bool mHasInputFilename;
    std::string mInputFilename;
    int mInputWidth;
    int mInputHeight;
    int mNumInputChannels;
    int mNumberInput;
    int mNumConvLayers;
    int mConvFilterSize;
    int mNumFullyConnLayers;
    int mOutputDim;
    NetworkMode mNetworkMode;
    std::string mNetworkName;
    bool mHasNetworkName;
    bool mGeneratePrototxt;
    bool mIsValidInput;
    int mThresholdPercent;
    bool mHasThreshold;

    void init();
    void debug();
    bool getNetworkCharacteristics();
    bool getInputDimensions(bool withInputFile);
    bool getPrototxt();
    int getThresholdPercentage();
    void setInputFilename(std::string filename);
    void setInputDimensions(int size, int num_channels, int num_input);
    void setBatchSize(int batch_size);
    void setNumConvolutionLayers(int num_convolution);
    void setConvolutionFilterSize(int conv_filter_size);
    void setNumFullyConnectedLayers(int num_fullyconn);
    void setOutputDimension(int output_dim);
    void setNetworkMode(NetworkMode network_mode);
    void setThresholdPercent(int threshold_percent);

public:
    UserInput(bool withInput);
    ~UserInput();
    bool isValidInput();
    bool doGeneratePrototxt();
    bool hasInputFilename();
    std::string getInputFilename();
    int getInputWidth();
    int getInputHeight();
    int getNumInputChannels();
    int getNumberInput();
    int getNumConvLayers();
    int getConvFilterSize();
    int getNumFullyConnLayers();
    int getOutputDim();
    NetworkMode getNetworkMode();
    int getThreshold();
    bool hasThreshold();
    std::string getNetworkName();
    std::string toString();
};

static bool isProperNumberInput(int num_input);
static bool isPowerOfTwo(int num);
static bool isProperNumChannels(int num_channels);
static bool isProperBatchSize(int batch_size);
static bool isProperConvSetting(int num_conv);
static bool isProperFullyConnectedSetting(int num_fc);
static bool isProperOutputDimSetting(int output_dim);
static NetworkMode getNetworkModeSetting(std::string mode_str);

#endif //RESEARCHDNNGENERATOR_USERINPUT_H
