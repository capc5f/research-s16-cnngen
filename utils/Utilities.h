//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_UTILITIES_H
#define RESEARCHDNNGENERATOR_UTILITIES_H

#include "../layers/LayerBase.h"
#include "../layers/InputLayer.h"
#include "../layers/ConvolutionLayer.h"
#include "../layers/PoolingLayer.h"
#include "../layers/ReLULayer.h"
#include "../layers/LRNLayer.h"
#include "../layers/InnerProductLayer.h"
#include "../layers/SoftmaxLayer.h"
#include "UserInput.h"

std::vector <LayerBase *> getAlexNetLayers();

void displayPrototxtOutput(UserInput in, std::vector<LayerBase *> layers, bool displayLayerSizes);


#endif //RESEARCHDNNGENERATOR_UTILITIES_H
