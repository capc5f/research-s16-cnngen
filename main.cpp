#include <iostream>
#include <string>
#include <vector>

#include "layers/InputLayer.h"
#include "layers/ConvolutionLayer.h"
#include "layers/PoolingLayer.h"
#include "layers/ReLULayer.h"
#include "layers/LRNLayer.h"
#include "layers/InnerProductLayer.h"
#include "layers/SoftmaxLayer.h"
#include "prototxt/Prototxt.h"
#include "utils/UserInput.h"
#include "utils/GenerateLayers.h"

using namespace std;

std::vector <LayerBase *> getAlexNetLayers();

int main(int argc, const char **argv) {

    UserInput in(false);
    if ( !in.isValidInput() ) {
        cout << "Exiting program.." << endl;
        return EXIT_FAILURE;
    }

    GenerateLayers gen(in);
    vector <LayerBase *> layers;
    layers = gen.getLayerList();
//    layers = getAlexNetLayers();

    if ( in.doGeneratePrototxt() ) {
        string dir = "/Users/styles/Code/Research_S16/output_files/";
        string filename = "test.prototxt";
        string network_name = "Layers_Test";
/*
        cout << "Generating prototxt named <" << filename << "> in directory <" << dir << ">" << endl;
        Prototxt *prototxt = new Prototxt(dir + filename, network_name, layers);
        prototxt->writeLayersToPrototxt();
*/
        cout << "name: \"" << network_name << "\"" << endl;
        for (unsigned long i = 0; i < layers.size(); ++i) {
            switch (layers.at(i)->getLayerType()) {
                case INPUT: {
                    InputLayer *il = (InputLayer *) layers.at(i);
                    if (il != NULL) {
                        cout << il->toString();
                       // cout << "Input layer size: W = " << il->getWidth() << ", H = " << il->getHeight() << endl;
                    }
                    break;
                }

                case CONVOLUTION: {
                    ConvolutionLayer *cl = (ConvolutionLayer *) layers.at(i);
                    if (cl != NULL) {
                        cout << cl->toString();
                        cout << "Convolution layer size: W = " << cl->getWidth() << ", H = " << cl->getHeight() << endl;
                    }
                    break;
                }

                case POOLING: {
                    PoolingLayer *pl = (PoolingLayer *) layers.at(i);
                    if (pl != NULL) {
                        cout << pl->toString();
                        cout << "Pooling layer size: W = " << pl->getWidth() << ", H = " << pl->getHeight() << endl;
                    }
                    break;
                }

                case RELU: {
                    ReLULayer *rl = (ReLULayer *) layers.at(i);
                    if (rl != NULL) {
                        cout << rl->toString();
                        cout << "ReLU layer size: W = " << rl->getWidth() << ", H = " << rl->getHeight() << endl;
                    }
                    break;
                }

                case INNER_PRODUCT: {
                    InnerProductLayer *ipl = (InnerProductLayer *) layers.at(i);
                    if (ipl != NULL) {
                        cout << ipl->toString();
                        cout << "Fully connected layer size: W = " << ipl->getWidth() << ", H = " << ipl->getHeight() << endl;
                    }
                    break;
                }

                default: {
                    break;
                }
            }
        }
    }

    layers.clear();
    if ( layers.empty() )
        cout << "Layers cleared.." << endl;

    return EXIT_SUCCESS;
}

std::vector <LayerBase *> getAlexNetLayers() {
    std::vector <LayerBase *> layers;

    InputLayer *data = new InputLayer("data", 1, 3, 32, 32);
    data->setTop("data");

    ConvolutionLayer *conv1 = new ConvolutionLayer("conv1", 32, 2, 5, 1, 2);
    conv1->setBottom("data");
    conv1->setTop("conv1");
    conv1->setParamAtIndex(0, 1, 0);
    conv1->setParamAtIndex(1, 2, 0);

    PoolingLayer *pool1 = new PoolingLayer("pool1", MAX, 3, 2);
    pool1->setBottom("conv1");
    pool1->setTop("pool1");

    ReLULayer *relu1 = new ReLULayer("relu1");
    relu1->setBottom("relu1");
    relu1->setTop("pool1");

    LRNLayer *norm1 = new LRNLayer("norm1", 3, 5e-05, 0.75, WITHIN_CHANNEL);
    norm1->setBottom("pool1");
    norm1->setTop("norm1");

    ConvolutionLayer *conv2 = new ConvolutionLayer("conv2", 32, 2, 5, 1);
    conv2->setBottom("norm1");
    conv2->setTop("conv2");
    conv2->setParamAtIndex(0, 1, 0);
    conv2->setParamAtIndex(1, 2, 0);

    ReLULayer *relu2 = new ReLULayer("relu2");
    relu2->setBottom("conv2");
    relu2->setTop("conv2");

    PoolingLayer *pool2 = new PoolingLayer("pool2", AVERAGE, 3, 2);
    pool2->setBottom("conv2");
    pool2->setTop("pool2");

    LRNLayer *norm2 = new LRNLayer("norm2", 3, 5e-05, 0.75, WITHIN_CHANNEL);
    norm1->setBottom("pool2");
    norm1->setTop("norm2");

    ConvolutionLayer *conv3 = new ConvolutionLayer("conv3", 64, 2, 5, 1);
    conv3->setBottom("norm2");
    conv3->setTop("conv3");

    ReLULayer *relu3 = new ReLULayer("relu3");
    relu2->setBottom("conv3");
    relu2->setTop("conv3");

    PoolingLayer *pool3 = new PoolingLayer("pool3", AVERAGE, 3, 2);
    pool3->setBottom("conv3");
    pool3->setTop("pool3");

    InnerProductLayer *ip1 = new InnerProductLayer("ip1", 10);
    ip1->setParamAtIndex(0, 1, 250);
    ip1->setParamAtIndex(1, 2, 0);

    SoftMaxLayer *prob = new SoftMaxLayer("prob");
    prob->setBottom("ip1");
    prob->setTop("prob");

    layers.push_back(data);
    layers.push_back(conv1);
    layers.push_back(pool1);
    layers.push_back(relu1);
    layers.push_back(norm1);
    layers.push_back(conv2);
    layers.push_back(relu2);
    layers.push_back(pool2);
    layers.push_back(norm2);
    layers.push_back(conv3);
    layers.push_back(relu3);
    layers.push_back(pool3);
    layers.push_back(ip1);
    layers.push_back(prob);

    return layers;
}