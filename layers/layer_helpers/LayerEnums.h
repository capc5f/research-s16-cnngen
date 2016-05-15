//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_LAYERENUMS_H
#define RESEARCHDNNGENERATOR_LAYERENUMS_H

enum LayerType {
    INPUT, CONVOLUTION, POOLING, LRN, RELU, INNER_PRODUCT, SOFTMAX
};

enum WeightFiller {
    XAVIER, GAUSSIAN
};

enum BiasFiller {
    CONSTANT
};

#endif //RESEARCHDNNGENERATOR_LAYERENUMS_H
