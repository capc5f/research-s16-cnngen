//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "Prototxt.h"

Prototxt::Prototxt(std::string prototxt_filename, std::string networkName) {
    setPrototxtFilename(prototxt_filename);
    setNetworkName(networkName);
}

Prototxt::Prototxt(std::string prototxt_filename, std::string networkName, std::vector <LayerBase *> layers) {
    setPrototxtFilename(prototxt_filename);
    setNetworkName(networkName);
    addLayers(layers);
}

Prototxt::~Prototxt() {

}

bool Prototxt::verifyFilename(std::string) {
    return true;
}

void Prototxt::addLayers(std::vector <LayerBase *> layers) {
    mLayers = layers;
}

void Prototxt::writeLayersToPrototxt() {
    std::ofstream writer(mPrototxtFilename);

    if ( !writer ) {
        std::cout << "Error opening file <" << mPrototxtFilename << ">" << std::endl;
        return;
    } else {
        writer << "name: \"";
        writer << mNetworkName << "\"" << std::endl;
        for (int i = 0; i < mLayers.size(); ++i) {
            writer << mLayers.at(i)->toString();
        }

        writer.close();
    }
}

std::string Prototxt::getPrototxtFilename() {
    return this->mPrototxtFilename;
}

void Prototxt::setPrototxtFilename(std::string prototxt_filename) {
    this->mPrototxtFilename = prototxt_filename;
}

std::string Prototxt::getNetworkName() {
    return this->mNetworkName;
}

void Prototxt::setNetworkName(std::string networkName) {
    this->mNetworkName = networkName;
}
