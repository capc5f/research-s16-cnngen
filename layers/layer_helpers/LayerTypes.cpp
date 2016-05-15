//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "LayerTypes.h"

/**
 * Layer Categories
 */
LayerCategory::LayerCategory(LayerCat layer_category) {
    setLayerCategory(layer_category);
}

LayerCategory::~LayerCategory() {

}

std::string LayerCategory::getLayerCategory() {
    switch ( mLayerCategory ) {
        case VISION:
            return "vision";

        case LOSS:
            return "loss";

        case ACTIVATION:
            return "activation";

        case DATA:
            return "data";

        case COMMON:
            return "common";

        default:
            return "";
    }
}

void LayerCategory::setLayerCategory(LayerCat layer_category) {
    this->mLayerCategory = layer_category;
}

/**
 * Vision Layers
 */
VisionLayers::VisionLayers(LayerType layer_type): LayerCategory(VISION) {
    setLayerType(layer_type);
}

VisionLayers::~VisionLayers() {

}

std::string VisionLayers::getLayerType() {
    switch ( mLayerType ) {
        case CONVOLUTION:
            return "Convolution";

        case POOLING:
            return "Pooling";

        case LRN:
            return "Local Response Normalization";

        default:
            return "";
    }
}

void VisionLayers::setLayerType(LayerType layer_type) {
    this->mLayerType = layer_type;
}

/**
 * Loss Layers
 */
LossLayers::LossLayers(LayerType layer_type): LayerCategory(LOSS) {
    setLayerType(layer_type);
}

LossLayers::~LossLayers() {

}

std::string LossLayers::getLayerType() {
    switch ( mLayerType ) {
        case SOFTMAX:
            return "Softmax";

        case EUCLIDEAN:
            return "Sum-of-Squares / Euclidean";

        case HINGELOSS:
            return "Hinge / Margin";

        case SIGMOID_WITH_LOSS:
            return "Sigmoid Cross-Entropy";

        default:
            return "";
    }
}

void LossLayers::setLayerType(LayerType layer_type) {
    this->mLayerType = layer_type;
}

/**
 * Activation Layers
 */
ActivationLayers::ActivationLayers(LayerType layer_type): LayerCategory(ACTIVATION) {
    setLayerType(layer_type);
}

ActivationLayers::~ActivationLayers() {

}

std::string ActivationLayers::getLayerType() {
    switch ( mLayerType ) {
        case RELU:
            return "ReLU / Rectified-Linear and Leaky-ReLU";

        case SIGMOID:
            return "Sigmoid";

        case TANH:
            return "TanH / Hyperbolic Tangent";

        case ABSVAL:
            return "Absolute Value";

        case POWER:
            return "Power";

        case BNLL:
            return "BNLL";

        default:
            return "";
    }
}

void ActivationLayers::setLayerType(LayerType layer_type) {
    this->mLayerType = layer_type;
}

/**
 * Data Layers
 */
DataLayers::DataLayers(LayerType layer_type): LayerCategory(DATA) {
    setLayerType(layer_type);
}

DataLayers::~DataLayers() {

}

std::string DataLayers::getLayerType() {
    switch ( mLayerType ) {
        case DATABASE:
            return "Database";

        case MEMORY:
            return "In-Memory";

        case HDF5_DATA:
            return "HDF5 Input";

        case HDF5_OUTPUT:
            return "HDF5 Output";

        case IMAGE_DATA:
            return "Images";

        default:
            return "";
    }
}

void DataLayers::setLayerType(LayerType layer_type) {
    this->mLayerType = layer_type;
}

/**
 * Common Layers
 */
CommonLayers::CommonLayers(LayerType layer_type): LayerCategory(COMMON) {
    setLayerType(layer_type);
}

CommonLayers::~CommonLayers() {

}

std::string CommonLayers::getLayerType() {
    switch ( mLayerType ) {
        case INNER_PRODUCT:
            return "Inner Product";

        case SPLIT:
            return "Splitting";

        case FLATTEN:
            return "Flattening";

        case RESHAPE:
            return "Reshape";

        case CONCAT:
            return "Concatenation";

        case SLICE:
            return "Slicing";

        default:
            return "";
    }
}

void CommonLayers::setLayerType(LayerType layer_type) {
    this->mLayerType = layer_type;
}
