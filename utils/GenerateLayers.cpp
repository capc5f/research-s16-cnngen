//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "GenerateLayers.h"

GenerateLayers::GenerateLayers(UserInput in) {
    init();

    this->mNumConvLayers = in.getNumConvLayers();
    this->mConvFilterSize = in.getConvFilterSize();
    this->mNumFullyConnLayers = in.getNumFullyConnLayers();
    this->mOutputDim = in.getOutputDim();
    this->mInputWidth = in.getInputWidth();
    this->mInputHeight = in.getInputHeight();
    this->mNumInputChannels = in.getNumInputChannels();
    this->mNumberInput = in.getNumberInput();
    this->mNetworkMode = in.getNetworkMode();
    if ( in.hasThreshold() )
        this->mThreshold = in.getThreshold() / 100.0;

    buildLayerList();
    setTopAndBottom();
    setTotalLayers();
}

void GenerateLayers::init() {
    mThreshold = 100.0;
    mTotalLayers = 0;
    mNumConvUsed = 0;
    mNumPoolUsed = 0;
    mNumReluUsed = 0;
    mNumFullyConnUsed = 0;
}

std::vector <LayerBase *> GenerateLayers::getLayerList() {
    return this->mLayerList;
}

// todo: FUTUREWORK -- integrate other layers and layer generating patterns..
void GenerateLayers::buildLayerList() {
    int i, size = mInputHeight;
    std::vector <LayerBase *> layers;
    {
        InputLayer *in = buildInputLayer();
        layers.push_back(in);
    }

    int N, M, K = mNumFullyConnLayers - 1, j;
    switch ( mNetworkMode ) {

        case AUTOMATIC: {

            /**
             * Follow pattern:
             * INPUT -> [[CONV -> RELU]*N -> POOL?]*M -> [FC -> RELU]*K -> FC
             *  - N:
             *  - M:
             *  - K:
             * always do at least 1 fully connected layer (linear classifier)
             * N >= 0, usually N <= 3, M >= 0, K >= 0 (and usually K < 3).
             */
            std::random_device rd;
            if ( mNumConvLayers > 0 ) {
                N = rd() % mNumConvLayers;
                M = mNumConvLayers / N;
            } else {
                M = N = 0;
            }

            for ( i = 0; i < M; ++i ) {
                for ( j = 0; j < N; ++j ) {
                    ConvolutionLayer *c = buildConvolutionLayer(size, size, mConvFilterSize, mNumInputChannels);
//                    ReLULayer *r = buildReLULayer(c->getOutputWidth());
                    ReLULayer *r = buildReLULayer(c->getOutputWidth(), c->getOutputHeight(), c->getOutputDepth());
                    layers.push_back(c);
                    layers.push_back(r);
                }

                PoolingLayer *p = buildPoolingLayerMax2by2(layers.back()->getOutputWidth(), layers.back()->getOutputDepth());
                layers.push_back(p);
                size = p->getOutputWidth();
            }

            /*
            for ( i = 0; i < K; ++i ) {
                InnerProductLayer *ip = buildInnerProductLayer(size, size);
                ReLULayer *r = buildReLULayer(size);
                layers.push_back(ip);
                layers.push_back(r);
            }

            InnerProductLayer *ip = buildInnerProductLayer(size, size, 1, mOutputDim);
            layers.push_back(ip);
            */
            break;
        }

        case THRESHOLD: {

            /**
             * Follow pattern:
             * INPUT -> {[CONV -> RELU -> POOL] * N } -> {[CONV -> RELU] * M } -> { [FC -> RELU] * K } -> FC
             *  - N: variable, determined based on the requested minimization ratio percentage
             *  - M: variable, leftover convolutions are chained, followed by relu
             *  - K: number of fully connected layers requested - 1
             *  always do at least 1 fully connected layer
             */

            double ratio = size / (double) mInputHeight;
            M = mNumConvLayers;

            while ( ratio >= mThreshold ) {
                if ( mNumConvUsed < mNumConvLayers ) {
                    ConvolutionLayer *c = buildConvolutionLayer(size, size, mConvFilterSize, mNumInputChannels);
//                    ReLULayer *r = buildReLULayer(size);
                    ReLULayer *r = buildReLULayer(c->getOutputWidth(), c->getOutputHeight(), c->getOutputDepth());
                    layers.push_back(c);
                    layers.push_back(r);
                }
                PoolingLayer *p = buildPoolingLayerMax2by2(size, layers.back()->getOutputDepth());
                layers.push_back(p);
                size = p->getOutputWidth();
                ratio = size / (float) mInputHeight;
            }

            for ( i = mNumConvUsed; i < M; ++i ) {
                ConvolutionLayer *c = buildConvolutionLayer(size, size, mConvFilterSize, mNumInputChannels);
//                ReLULayer *r = buildReLULayer(size);
                ReLULayer *r = buildReLULayer(c->getOutputWidth(), c->getOutputHeight(), c->getOutputDepth());
                layers.push_back(c);
                layers.push_back(r);
            }

            /*
            for ( i = 0; i < K; ++i ) {
                InnerProductLayer *ip = buildInnerProductLayer(size, size);
                ReLULayer *r = buildReLULayer(size);
                layers.push_back(ip);
                layers.push_back(r);
            }

            InnerProductLayer *ip = buildInnerProductLayer(size, size, 1, mOutputDim);
            layers.push_back(ip);
            */
            break;
        }
    }

    int in_w, in_h, in_d, out_w = 1, out_h = 1, out_d = mOutputDim;
    for ( i = 0; i < K; ++i ) {
        in_w = layers.back()->getOutputWidth();
        in_h = layers.back()->getOutputHeight();
        in_d = layers.back()->getOutputDepth();
        InnerProductLayer *ip = buildInnerProductLayer(in_w, in_h, in_d, out_w, out_h, out_d);
//        ReLULayer *r = buildReLULayer(size);
        ReLULayer *r = buildReLULayer(ip->getOutputWidth(), ip->getOutputHeight(), ip->getOutputDepth());
        layers.push_back(ip);
        layers.push_back(r);
    }

//    InnerProductLayer *ip = buildInnerProductLayer(size, size, 1, mOutputDim);
    InnerProductLayer *ip = buildInnerProductLayer(layers.back()->getOutputWidth(), layers.back()->getOutputHeight(), layers.back()->getOutputDepth(), 1, 1, mOutputDim);
    layers.push_back(ip);

    mLayerList = layers;
}

InputLayer* GenerateLayers::buildInputLayer() {
    InputLayer *inputLayer = new InputLayer("input", mNumberInput, mNumInputChannels, mInputHeight, mInputWidth);

    return inputLayer;
}

/**
 * convolution equations:
 *  W2 = [ (W1 - F + 2P) / S ] + 1
 *  P = (F - 1) / 2
 */
ConvolutionLayer* GenerateLayers::buildConvolutionLayer(int in_size, int f_size, int depth) {
    std::stringstream ss;
    ss << "conv" << ++mNumConvUsed;

    int p = checkConvPadding(f_size);
    if ( p < 0) {
        std::cerr << "Error: incompatible filter size for convolution layer <" << ss.str() << ">" << std::endl;
        std::cerr.flush();
        return nullptr;
    }

    int s = 1;
    int W2 = ( (in_size - f_size + 2*p ) / s ) + 1;

    ConvolutionLayer *convolutionLayer = new ConvolutionLayer(ss.str(), depth, p, f_size, s);
    convolutionLayer->setInputWidth(W2);
    convolutionLayer->setInputHeight(W2);
    convolutionLayer->setOutputWidth(W2);
    convolutionLayer->setOutputHeight(W2);

    return convolutionLayer;
}

ConvolutionLayer* GenerateLayers::buildConvolutionLayer(int in_width, int in_height, int f_size, int depth) {
    std::stringstream ss;
    ss << "conv" << ++mNumConvUsed;

    int p = checkConvPadding(f_size);
    if ( p < 0) {
        std::cerr << "Error: incompatible filter size for convolution layer <" << ss.str() << ">" << std::endl;
        std::cerr.flush();
        return nullptr;
    }

    int s = 1, W1 = in_width, H1 = in_height;
    int W2 = ( (W1 - f_size + 2*p ) / s ) + 1;
    int H2 = ( (H1 - f_size + 2*p) / s ) + 1;

    ConvolutionLayer *convolutionLayer = new ConvolutionLayer(ss.str(), depth, p, f_size, s);
    convolutionLayer->setInputWidth(W1);
    convolutionLayer->setInputHeight(H1);
    convolutionLayer->setOutputWidth(W2);
    convolutionLayer->setOutputHeight(H2);

    return convolutionLayer;
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
    poolingLayer->setInputDepth(mNumInputChannels);
    poolingLayer->setOutputDepth(mNumInputChannels);

    return poolingLayer;
}

/**
* Pooling equations:
*  W2 = [ (W1 - F) / S ] + 1
*/
PoolingLayer* GenerateLayers::buildPoolingLayerMax2by2(int in_size, int depth) {
    int filter_size = 2, stride = 2;
    std::stringstream ss;
    ss << "pool" << ++mNumPoolUsed;

    PoolingLayer *poolingLayer = new PoolingLayer(ss.str(), MAX, filter_size, stride);
    int W2 = ( (in_size - filter_size ) / stride ) + 1;

    poolingLayer->setInputHeight(in_size);
    poolingLayer->setInputWidth(in_size);
    poolingLayer->setOutputHeight(W2);
    poolingLayer->setOutputWidth(W2);
    poolingLayer->setInputDepth(depth);
    poolingLayer->setOutputDepth(depth);

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
    reLULayer->setInputDepth(mNumInputChannels);
    reLULayer->setOutputDepth(mNumInputChannels);

    return reLULayer;
}

ReLULayer* GenerateLayers::buildReLULayer(int width, int height, int depth) {
    std::stringstream ss;
    ss << "relu" << ++mNumReluUsed;

    ReLULayer *reLULayer = new ReLULayer(ss.str());
    reLULayer->setInputHeight(height);
    reLULayer->setInputWidth(width);
    reLULayer->setInputDepth(depth);
    reLULayer->setOutputHeight(height);
    reLULayer->setOutputWidth(width);
    reLULayer->setOutputDepth(depth);

    return reLULayer;
}

InnerProductLayer* GenerateLayers::buildInnerProductLayer(int in_size, int out_size) {
    std::stringstream ss;
    ss << "fc" << ++mNumFullyConnUsed;

    InnerProductLayer *innerProductLayer = new InnerProductLayer(ss.str(), out_size);
    innerProductLayer->setInputHeight(in_size);
    innerProductLayer->setInputWidth(in_size);
    innerProductLayer->setOutputHeight(out_size);
    innerProductLayer->setOutputWidth(out_size);

    return innerProductLayer;
}

InnerProductLayer* GenerateLayers::buildInnerProductLayer(int in_width, int in_height, int out_width,
                                                          int out_height) {
    std::stringstream ss;
    ss << "fc" << ++mNumFullyConnUsed;

    InnerProductLayer *innerProductLayer = new InnerProductLayer(ss.str(), in_width, in_height, out_width, out_height);

    return innerProductLayer;
}

InnerProductLayer* GenerateLayers::buildInnerProductLayer(int in_width, int in_height, int in_depth, int out_width, int out_height, int out_depth) {
    std::stringstream ss;
    ss << "fc" << ++mNumFullyConnUsed;

    InnerProductLayer *innerProductLayer = new InnerProductLayer(ss.str(), in_width, in_height, out_width, out_height);
    innerProductLayer->setInputDepth(in_depth);
    innerProductLayer->setOutputDepth(out_depth);

    return innerProductLayer;
}

void GenerateLayers::setTopAndBottom() {
    std::vector<LayerBase *>::iterator iter;
    std::string top;
    std::string bottom;
    for ( iter = mLayerList.begin(); iter != mLayerList.end(); ++iter ) {
        if ( iter != mLayerList.begin() )
            (*iter)->setBottom(bottom);
        top = (*iter)->getName();
        (*iter)->setTop(top);
        bottom = (*iter)->getName();
    }
}

void GenerateLayers::setTotalLayers() {
    this->mTotalLayers = mLayerList.size();
}

unsigned long GenerateLayers::getTotalNumberLayers() {
    return this->mTotalLayers;
}

int checkConvPadding(int filter_size) {
    int pad = ( filter_size - 1 );
    if ( pad % 2 != 0 )
        return -1;
    else
        return pad / 2;
}
