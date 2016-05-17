//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "Utilities.h"

using namespace std;

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

void displayPrototxtOutput(UserInput in, std::vector<LayerBase *> layers, bool displayLayerSizes) {
    if ( layers.empty() )
        return;

    string dir = "/Users/styles/Code/Research_S16/output_files/"; // todo: FIXME
    string filename = in.getInputFilename();
    string network_name = in.getNetworkName();
    stringstream ss;
/*
        cout << "Generating prototxt named <" << filename << "> in directory <" << dir << ">" << endl;
        Prototxt *prototxt = new Prototxt(dir + filename, network_name, layers);
        prototxt->writeLayersToPrototxt();
*/

    cout << "\nSnapshot of the generated prototxt file:\n" << "name: \"" << network_name << "\"" << endl;
    for (unsigned long i = 0; i < layers.size(); ++i) {
        switch (layers.at(i)->getLayerType()) {
            case INPUT: {
                InputLayer *il = (InputLayer *) layers.at(i);
                if (il != NULL) {
                    cout << il->toString();
                    ss << i << ") layer: " << il->getName() << " [w,h,d] -> in_dims [" << il->getInputWidth() << ", " << il->getInputHeight() << ", " << il->getInputDepth() << "] | ";
                    ss << "out_dims [" << il->getOutputWidth() << ", " << il->getOutputHeight() << ", " << il->getOutputDepth() << "]" << endl;
                }
                break;
            }

            case CONVOLUTION: {
                ConvolutionLayer *cl = (ConvolutionLayer *) layers.at(i);
                if (cl != NULL) {
                    cout << cl->toString();
                    ss << i << ") layer: " << cl->getName() << " [w,h,d] -> in_dims [" << cl->getInputWidth() << ", " << cl->getInputHeight() << ", " << cl->getInputDepth() << "] | ";
                    ss << "out_dims [" << cl->getOutputWidth() << ", " << cl->getOutputHeight() << ", " << cl->getOutputDepth() << "]" << endl;
                }
                break;
            }

            case POOLING: {
                PoolingLayer *pl = (PoolingLayer *) layers.at(i);
                if (pl != NULL) {
                    cout << pl->toString();
                    ss << i << ") layer: " << pl->getName() << " [w,h,d] -> in_dims [" << pl->getInputWidth() << ", " << pl->getInputHeight() << ", " << pl->getInputDepth() << "] | ";
                    ss << "out_dims [" << pl->getOutputWidth() << ", " << pl->getOutputHeight() << ", " << pl->getOutputDepth() << "]" << endl;
                }
                break;
            }

            case RELU: {
                ReLULayer *rl = (ReLULayer *) layers.at(i);
                if (rl != NULL) {
                    cout << rl->toString();
                    ss << i << ") layer: " << rl->getName() << " [w,h,d] -> in_dims [" << rl->getInputWidth() << ", " << rl->getInputHeight() << ", " << rl->getInputDepth() << "] | ";
                    ss << "out_dims [" << rl->getOutputWidth() << ", " << rl->getOutputHeight() << ", " << rl->getOutputDepth() << "]" << endl;
                }
                break;
            }

            case INNER_PRODUCT: {
                InnerProductLayer *ipl = (InnerProductLayer *) layers.at(i);
                if (ipl != NULL) {
                    cout << ipl->toString();
                    ss << i << ") layer: " << ipl->getName() << " [w,h,d] -> in_dims [" << ipl->getInputWidth() << ", " << ipl->getInputHeight() << ", " << ipl->getInputDepth() << "] | ";
                    ss << "out_dims [" << ipl->getOutputWidth() << ", " << ipl->getOutputHeight() << ", " << ipl->getOutputDepth() << "]" << endl;
                }
                break;
            }

            default: {
                break;
            }
        }
    }

    if (displayLayerSizes)
        cout << ss.str();
}

vector<Image *> buildImageList(UserInput in) {
    string file = in.getInputFilename();
    vector<Image *> imageList;

    char byte;
    int i, j;
    // Read bytes from a file using an input file stream
    ifstream reader(file);

    if ( !reader ) {
        cout << "Error opening file" << endl;
    } else {
        // Read each character from the stream until end of file
        for ( int i = 0; !reader.eof(); i++){

            // Get the next byte and output it
            reader.get(byte);

        }

        cout << endl;
        reader.close();
    }

    return imageList;
}

uint8_t* getImageAtOffset(UserInput in, int batch_size, int batch_num) {
    string file = in.getInputFilename();
    const int image_size = in.getInputWidth() * in.getInputHeight() * in.getNumInputChannels();
    const int size = batch_size * image_size;
    char *imageArray = NULL;

    ifstream reader(file, std::ifstream::binary);

    if ( !reader ) {
        cerr << "Error opening input file <" << file << ">" << endl;
        cerr.flush();
    } else {
        imageArray = new char[size];
        reader.read(imageArray + batch_num*image_size + 1, size);
        reader.close();
    }

    return (uint8_t *) imageArray;
}

std::vector<ImageBatch *> buildBatchList(UserInput in, int batch_size) {
    vector<ImageBatch *> batchList;
    int num_batches = in.getNumberInput() / batch_size;
    int rem_batch = in.getNumberInput() % batch_size; // todo: FIXME: FUTUREWORK -- the remainder is ignored
    int image_size = in.getInputWidth() * in.getInputHeight() * in.getNumInputChannels();

    cout << "num_batches: " << num_batches << ", rem_batch: " << rem_batch << ", image_size: " << image_size << endl;

    for ( int i = 0; i < num_batches; ++i ) {
        uint8_t* data = getImageAtOffset(in, batch_size, i);
        cout << "Got image data #" << i << endl;
        ImageBatch *ib = new ImageBatch(image_size, data);
        cout << "Made ImageBatch obj #" << ib->getBatchId();
        batchList.push_back(ib);
    }

    return batchList;
}

void destroyBatchList(std::vector<ImageBatch *> batch_list) {
    batch_list.clear();
}
