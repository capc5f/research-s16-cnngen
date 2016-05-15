//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_LAYERTYPES_H
#define RESEARCHDNNGENERATOR_LAYERTYPES_H



#include <string>

class LayerCategory {
protected:
    enum LayerCat {
        VISION, LOSS, ACTIVATION, DATA, COMMON
    };

private:
    LayerCat mLayerCategory;

public:
    LayerCategory(LayerCat layer_category);
    ~LayerCategory();
    std::string getLayerCategory();
    void setLayerCategory(LayerCat layer_category);
};

class VisionLayers: public LayerCategory {
private:
    enum LayerType {
        CONVOLUTION, POOLING, LRN
    };
    LayerType mLayerType;

public:
    VisionLayers(LayerType layer_type);
    ~VisionLayers();
    std::string getLayerType();
    void setLayerType(LayerType layer_type);
};

class LossLayers: public LayerCategory {
private:
    enum LayerType {
        SOFTMAX, EUCLIDEAN, HINGELOSS, SIGMOID_WITH_LOSS
    };
    LayerType mLayerType;

public:
    LossLayers(LayerType layer_type);
    ~LossLayers();
    std::string getLayerType();
    void setLayerType(LayerType layer_type);
};

class ActivationLayers: public LayerCategory {
private:
    enum LayerType {
        RELU, SIGMOID, TANH, ABSVAL, POWER, BNLL
    };
    LayerType mLayerType;

public:
    ActivationLayers(LayerType layer_type);
    ~ActivationLayers();
    std::string getLayerType();
    void setLayerType(LayerType layer_type);
};

class DataLayers: public LayerCategory {
private:
    enum LayerType {
        DATABASE, MEMORY, HDF5_DATA, HDF5_OUTPUT, IMAGE_DATA
    };
    LayerType mLayerType;

public:
    DataLayers(LayerType layer_type);
    ~DataLayers();
    std::string getLayerType();
    void setLayerType(LayerType layer_type);
};

class CommonLayers: public LayerCategory {
private:
    enum LayerType {
        INNER_PRODUCT, SPLIT, FLATTEN, RESHAPE, CONCAT, SLICE
    };
    LayerType mLayerType;

public:
    CommonLayers(LayerType layer_type);
    ~CommonLayers();
    std::string getLayerType();
    void setLayerType(LayerType layer_type);
};



#endif //RESEARCHDNNGENERATOR_LAYERTYPES_H
