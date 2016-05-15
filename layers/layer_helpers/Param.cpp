//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "Param.h"

Param::Param(int lr_mult, int decay_mult) {
    setLearningRate(lr_mult);
    setDecayMult(decay_mult);
}

Param::Param(int lr_mult, int decay_mult, std::string name) {
    setLearningRate(lr_mult);
    setDecayMult(decay_mult);
    setName(name);
}

Param::Param(int lr_mult, int decay_mult, float std) {
    setLearningRate(lr_mult);
    setDecayMult(decay_mult);
    setStandardDeviation(std);
}

Param::Param(int lr_mult, int decay_mult, float std, std::string name) {
    setLearningRate(lr_mult);
    setDecayMult(decay_mult);
    setStandardDeviation(std);
    setName(name);
}

Param::~Param() {

}

std::string Param::getName() {
    return this->mName;
}

void Param::setName(std::string name) {
    this->mName = name;
}

int Param::getLearningRate() {
    return this->lr_mult;
}

void Param::setLearningRate(int lr_mult) {
    this->lr_mult = lr_mult;
}

int Param::getDecayMult() {
    return this->decay_mult;
}

void Param::setDecayMult(int decay_mult) {
    this->decay_mult = decay_mult;
}

float Param::getStandardDeviation() {
    return this->std;
}

void Param::setStandardDeviation(float std) {
    this->std = std;
}
