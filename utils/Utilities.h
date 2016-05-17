//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_UTILITIES_H
#define RESEARCHDNNGENERATOR_UTILITIES_H

#include <fstream>
#include <vector>

#include "../layers/LayerBase.h"
#include "../layers/InputLayer.h"
#include "../layers/ConvolutionLayer.h"
#include "../layers/PoolingLayer.h"
#include "../layers/ReLULayer.h"
#include "../layers/LRNLayer.h"
#include "../layers/InnerProductLayer.h"
#include "../layers/SoftmaxLayer.h"
#include "UserInput.h"
#include "../ece8270project/Image.h"
#include "../ece8270project/ImageBatch.h"

std::vector <LayerBase *> getAlexNetLayers();
void displayPrototxtOutput(UserInput in, std::vector<LayerBase *> layers, bool displayLayerSizes);
std::vector<Image *> buildImageList(UserInput in);
uint8_t* buildImageArray(UserInput in, int batch_size, int batch_num);
std::vector<ImageBatch *> buildBatchList(UserInput in, int batch_size);
void destroyBatchList(std::vector<ImageBatch *> batch_list);

#endif //RESEARCHDNNGENERATOR_UTILITIES_H
