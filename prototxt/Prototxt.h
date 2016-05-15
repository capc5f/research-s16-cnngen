//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_PROTOTXT_H
#define RESEARCHDNNGENERATOR_PROTOTXT_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../layers/LayerBase.h"

class Prototxt {
private:
    std::vector <LayerBase *> mLayers;
    std::string mPrototxtFilename;
    std::string mNetworkName;
    bool verifyFilename(std::string);

public:
    Prototxt(std::string prototxt_filename, std::string networkName);
    Prototxt(std::string prototxt_filename, std::string networkName, std::vector <LayerBase *> layers);
    Prototxt(std::string prototxt_filename, std::string networkName, std::string solver_filename, std::vector <LayerBase *> layers);
    ~Prototxt();
    void addLayers(std::vector <LayerBase *> layers);
    void writeLayersToPrototxt();
    std::string getPrototxtFilename();
    void setPrototxtFilename(std::string prototxt_filename);
    std::string getNetworkName();
    void setNetworkName(std::string networkName);
};


#endif //RESEARCHDNNGENERATOR_PROTOTXT_H
