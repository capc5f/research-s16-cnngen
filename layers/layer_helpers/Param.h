//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_PARAM_H
#define RESEARCHDNNGENERATOR_PARAM_H

#include <iostream>
#include <string>

class Param {
private:
    std::string mName;
    int lr_mult;
    int decay_mult;
    float std;

public:
    Param(int lr_mult, int decay_mult);
    Param(int lr_mult, int decay_mult, std::string name);
    Param(int lr_mult, int decay_mult, float std);
    Param(int lr_mult, int decay_mult, float std, std::string name);
    ~Param();
    std::string getName();
    void setName(std::string name);
    int getLearningRate();
    void setLearningRate(int lr_mult);
    int getDecayMult();
    void setDecayMult(int decay_mult);
    float getStandardDeviation();
    void setStandardDeviation(float std);
};

#endif //RESEARCHDNNGENERATOR_PARAM_H
