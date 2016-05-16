//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "GenerateLayers.h"

GenerateLayers::GenerateLayers(UserInput in) {
    mNumConvUsed = 0;
    mNumPoolUsed = 0;
    mNumReluUsed = 0;
    mNumFullyConnUsed = 0;

    this->mNumConvLayers = in.getNumConvLayers();
    this->mConvFilterSize = in.getConvFilterSize();
    this->mNumFullyConnLayers = in.getNumFullyConnLayers();
    this->mOutputDim = in.getOutputDim();
    this->mInputWidth = in.getInputWidth();
    this->mInputHeight = in.getInputHeight();
    this->mNumInputChannels = in.getNumInputChannels();
    this->mNetworkMode = in.getNetworkMode();
    this->mThreshold = in.getThreshold() / 100.0;

    buildLayerList();
}

std::vector <LayerBase *> GenerateLayers::getLayerList() {
    return this->mLayerList;
}

// todo: integrate network mode..
void GenerateLayers::buildLayerList() {
    int i, size = mInputHeight;
    std::vector <LayerBase *> layers;

    switch ( mNetworkMode ) {
        case AUTOMATIC: {

            for (i = 0; i < mNumConvLayers; ++i) {
                ConvolutionLayer *c = buildConvolutionLayer(size, mConvFilterSize, mNumInputChannels);
                ReLULayer *r = buildReLULayer(c->getOutputWidth());
                PoolingLayer *p = buildPoolingLayerMax2by2(c->getOutputWidth());
                layers.push_back(c);
                layers.push_back(r);
                layers.push_back(p);
                size = p->getOutputWidth();
            }

            for (i = 0; i < mNumFullyConnLayers; ++i) {
                InnerProductLayer *i = buildInnerProductLayer(size, mOutputDim);
                layers.push_back(i);
            }

            break;
        }

        case THRESHOLD: {

            double ratio = size / (double) mInputHeight;

            while ( ratio >= mThreshold ) {
                if ( mNumConvUsed < mNumConvLayers ) {
                    ConvolutionLayer *c = buildConvolutionLayer(size, mConvFilterSize, mNumInputChannels);
                    ReLULayer *r = buildReLULayer(size);
                    layers.push_back(c);
                    layers.push_back(r);
                }
                PoolingLayer *p = buildPoolingLayerMax2by2(size);
                layers.push_back(p);
                size = p->getOutputWidth();
                ratio = size / (float) mInputHeight;
            }

            for ( i = mNumConvUsed; i < mNumConvLayers; ++i ) {
                ConvolutionLayer *c = buildConvolutionLayer(size, mConvFilterSize, mNumInputChannels);
                ReLULayer *r = buildReLULayer(size);
                layers.push_back(c);
                layers.push_back(r);
            }

            for ( i = 0; i < mNumFullyConnLayers - 1; ++i ) {
                InnerProductLayer *ip = buildInnerProductLayer(size, size);
                ReLULayer *r = buildReLULayer(size);
                layers.push_back(ip);
                layers.push_back(r);
            }
            std::cout << "Size: " << size <<  ", Output dim: " << mOutputDim << std::endl;
            InnerProductLayer *ip = buildInnerProductLayer(size, mOutputDim);
            layers.push_back(ip);

            break;
        }
    }

    mLayerList = layers;
}

/**
 * convolution equations:
 *  W2 = [ (W1 - F + 2P) / S ] + 1
 *  P = (F - 1) / 2
 */
ConvolutionLayer* GenerateLayers::buildConvolutionLayer(int in_size, int f_size, int depth) {
    int p = checkConvPadding(f_size);
    if ( p < 0) {
        std::cerr << "Error: incompatible filter size for convolution layer!" << std::endl;
        std::cerr.flush();
        return nullptr;
    }

    int s = 1;
    int W2 = ( (in_size - f_size + 2*p ) / s ) + 1;

    std::stringstream ss;
    ss << "conv" << ++mNumConvUsed;
    ConvolutionLayer *convolutionLayer = new ConvolutionLayer(ss.str(), depth, p, f_size, s);
    convolutionLayer->setInputWidth(W2);
    convolutionLayer->setInputHeight(W2);
    convolutionLayer->setOutputWidth(W2);
    convolutionLayer->setOutputHeight(W2);

    return convolutionLayer;
}

int checkConvPadding(int filter_size) {
    int pad = ( filter_size - 1 );
    if ( pad % 2 != 0 )
        return -1;
    else
        return pad / 2;
}

/**
* Pooling equations:
*  W2 = [ (W1 - F) / S ] + 1
*/
PoolingLayer* GenerateLayers::buildPoolingLayer(int in_size, int filter_size, PoolingType type, int stride) {
    std::stringstream ss;
    ss << "pool" << ++mNumPoolUsed;

    PoolingLayer *poolingLayer = new PoolingLayer(ss.str(), type, filter_size, stride);
    int W2 = ( (in_size - filter_size ) / stride ) + 1;

    poolingLayer->setInputHeight(W2);
    poolingLayer->setInputWidth(W2);
    poolingLayer->setOutputHeight(W2);
    poolingLayer->setOutputWidth(W2);

    return poolingLayer;
}

/**
* Pooling equations:
*  W2 = [ (W1 - F) / S ] + 1
*/
PoolingLayer* GenerateLayers::buildPoolingLayerMax2by2(int in_size) {
    int filter_size = 2, stride = 2;
    std::stringstream ss;
    ss << "pool" << ++mNumPoolUsed;

    PoolingLayer *poolingLayer = new PoolingLayer(ss.str(), MAX, filter_size, stride);
    int W2 = ( (in_size - filter_size ) / stride ) + 1;

    poolingLayer->setInputHeight(W2);
    poolingLayer->setInputWidth(W2);
    poolingLayer->setOutputHeight(W2);
    poolingLayer->setOutputWidth(W2);

    return poolingLayer;
}

ReLULayer* GenerateLayers::buildReLULayer(int in_size) {
    std::stringstream ss;
    ss << "relu" << ++mNumReluUsed;

    ReLULayer *reLULayer = new ReLULayer(ss.str());
    reLULayer->setInputHeight(in_size);
    reLULayer->setInputWidth(in_size);
    reLULayer->setOutputHeight(in_size);
    reLULayer->setOutputWidth(in_size);

    return reLULayer;
}

InnerProductLayer* GenerateLayers::buildInnerProductLayer(int in_size, int out_size) {
    std::stringstream ss;
    ss << "ip" << ++mNumFullyConnUsed;

    InnerProductLayer *innerProductLayer = new InnerProductLayer(ss.str(), out_size);
    innerProductLayer->setInputHeight(in_size);
    innerProductLayer->setInputWidth(in_size);
    innerProductLayer->setOutputHeight(out_size);
    innerProductLayer->setOutputWidth(out_size);

    return innerProductLayer;
}
