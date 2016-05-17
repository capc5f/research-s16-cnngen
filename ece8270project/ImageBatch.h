//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_IMAGEBATCH_H
#define RESEARCHDNNGENERATOR_IMAGEBATCH_H

#include <cstdlib>
#include <cstdint>

class ImageBatch {
private:
    static int sNumberOfBatches;

    int mBatchId;
    int mLength;
    uint8_t* mData;
    float* mBatch;

    void init();
    void convert();

public:
    ImageBatch(int length, uint8_t* data);
    ~ImageBatch();
    static int totalNumBatches();
    float* get();
    void clean();
    int length();
    int getBatchId();
};


#endif //RESEARCHDNNGENERATOR_IMAGEBATCH_H
