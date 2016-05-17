//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "UserInput.h"

using namespace std;

UserInput::UserInput(bool withInputFile) {
    init();

#ifdef DEBUG

    debug();

#else

    if (!getInputDimensions(withInputFile)) {
        mIsValidInput = false;
        return;
    }

    if (!getNetworkCharacteristics()) {
        mIsValidInput = false;
        return;
    }

    mGeneratePrototxt = getPrototxt();
    if ( mGeneratePrototxt ) {
        cout << "Please name your generated network: ";
        cin >> mNetworkName;
        mHasNetworkName = true;
    }
#endif
}

UserInput::~UserInput() {

}

void UserInput::init() {
    mHasInputFilename = false;
    mIsValidInput = true;
    mHasNetworkName = false;
    mNetworkName = "generated_cnn";
    mNumberInput = 1;
}

void UserInput::debug() {
    mInputWidth = 32;
    mInputHeight = 32;
    mNumInputChannels = 3;
    mNumberInput = 3;
    mNumConvLayers = 3;
    mConvFilterSize = 3;
    mNumFullyConnLayers = 3;
    mOutputDim = 10;
    setBatchSize(128);
    mNetworkMode = AUTOMATIC;
    mGeneratePrototxt = true;
    mIsValidInput = true;
}

bool UserInput::isValidInput() {
    return this->mIsValidInput;
}

bool UserInput::doGeneratePrototxt() {
    return this->mGeneratePrototxt;
}

bool UserInput::hasInputFilename() {
    return this->mHasInputFilename;
}

bool UserInput::getInputDimensions(bool withInputFile) {
    int err_num = 0, size = -1, num_channels = -1, batch_size = -1, num_input = 1;
    string size_str, num_channels_str, filename, batch_size_str, num_input_str;
    bool flag, e_flag = false;

    if ( withInputFile ) {
        cout << "Please enter the input filename: ";
        cin >> filename;
        ifstream myfile(filename);

        if (myfile.is_open()) {
            mHasInputFilename = true;
            myfile.close();

            do {
                cout << "How images do you want to read from this file?" << endl;
                cin >> num_input_str;
                try {
                    num_input = stoi(num_input_str, nullptr, 10);
                } catch (const std::invalid_argument &ia) {
                    cerr << "Invalid argument: " << ia.what() << endl;
                    cerr.flush();
                    e_flag = true;
                }

                flag = isProperNumberInput(num_input);
                if (!flag) {
                    if (!e_flag)
                        cerr << "Error: <" << num_input << "> is not a valid number of images!" << endl;

                    if (++err_num >= 3)
                        return false;
                }
                e_flag = false;
                cerr.flush();
            } while ( !flag );

        } else {
            cerr << "Unable to open file <" << filename << ">" << endl;
            cerr.flush();
            return false;
        }
    }

    do {
        cout << "How big is the input image?" << endl
        << "Note: currently only supports square images." << endl
        << "This value should be either a width or height (one dimensional size) and a power of 2" << endl;
        cin >> size_str;
        try {
            size = stoi(size_str, nullptr, 10);
        } catch (const std::invalid_argument &ia) {
            cerr << "Invalid argument: " << ia.what() << endl;
            cerr.flush();
            e_flag = true;
        }

        flag = isPowerOfTwo(size);
        if (!flag) {
            if (!e_flag)
                cerr << "Error: <" << size << "> is not a valid input dimension!" << endl;

            if (++err_num >= 3)
                return false;
        }
        e_flag = false;
        cerr.flush();
    } while ( !flag );

    err_num = 0;
    do {
        cout << "How many channels does this image contain?" << endl;
        cin >> num_channels_str;
        try {
            num_channels = stoi(num_channels_str, nullptr, 10);
        } catch (const std::invalid_argument &ia) {
            cerr << "Invalid argument: " << ia.what() << endl;
            e_flag = true;
        }

        flag = isProperNumChannels(num_channels);
        if (!flag) {
            if (!e_flag)
                cerr << "Error: <" << num_channels << "> is not a valid number of input channels!" << endl;

            if (++err_num >= 3)
                return false;
        }
        e_flag = false;
        cerr.flush();
    } while ( !flag );

    err_num = 0;
    do {
        cout << "What batch size do you want?" << endl;
        cin >> batch_size_str;
        try {
            batch_size = stoi(batch_size_str, nullptr, 10);
        } catch (const std::invalid_argument &ia) {
            cerr << "Invalid argument: " << ia.what() << endl;
            e_flag = true;
        }

        flag = isProperBatchSize(batch_size);
        if (!flag) {
            if (!e_flag)
                cerr << "Error: <" << batch_size << "> is not a valid batch size!" << endl;

            if (++err_num >= 3)
                return false;
        }
        e_flag = false;
        cerr.flush();
    } while ( !flag );

    setInputFilename(filename);
    setInputDimensions(size, num_channels, num_input);
    setBatchSize(batch_size);

    return true;
}

bool UserInput::getNetworkCharacteristics() {
    string num_conv_str, conv_filter_size_str, num_fc_str, output_dim_str, mode_str, network_name_str;
    int num_conv = -1, conv_filter_size = -1, num_fc = -1, output_dim = -1, err_num = 0;
    NetworkMode mode;
    bool flag, e_flag = false;

    do {
        cout << "How many convolution layers would you like?" << endl;
        cin >> num_conv_str;
        try {
            num_conv = stoi(num_conv_str, nullptr, 10);
        } catch (const std::invalid_argument &ia) {
            cerr << "Invalid argument: " << ia.what() << endl;
            e_flag = true;
        }

        flag = isProperConvSetting(num_conv);
        if (!flag) {
            if (!e_flag)
                cerr << "Error: <" << num_conv << "> is not a valid number of convolution layers!" << endl;

            if (++err_num >= 3)
                return false;
        }
        e_flag = false;
        cerr.flush();
    } while (!flag);

    if ( num_conv > 0 ) {
        do {
            cout << "What convolution filter size would you like?" << endl;
            cin >> conv_filter_size_str;
            try {
                conv_filter_size = stoi(conv_filter_size_str, nullptr, 10);
            } catch (const std::invalid_argument &ia) {
                cerr << "Invalid argument: " << ia.what() << endl;
                e_flag = true;
            }

            flag = isProperConvSetting(conv_filter_size);
            if (!flag) {
                if (!e_flag)
                    cerr << "Error: <" << conv_filter_size << "> is not a valid convolution filter size!" << endl;

                if (++err_num >= 3)
                    return false;
            }
            e_flag = false;
            cerr.flush();
        } while (!flag);
    }

    do {
        cout << "How many fully connected layers would you like?" << endl;
        cin >> num_fc_str;
        try {
            num_fc = stoi(num_fc_str, nullptr, 10);
        } catch (const std::invalid_argument &ia) {
            cerr << "Invalid argument: " << ia.what() << endl;
            e_flag = true;
        }

        flag = isProperFullyConnectedSetting(num_fc);
        if (!flag) {
            if (!e_flag)
                cerr << "Error: <" << num_fc << "> is not a valid number of fully connected layers!" << endl;

            if (++err_num >= 3)
                return false;
        }
        e_flag = false;
        cerr.flush();
    } while (!flag);

    do {
        cout << "What size of output would you like?" << endl;
        cin >> output_dim_str;
        try {
            output_dim = stoi(output_dim_str, nullptr, 10);
        } catch (const std::invalid_argument &ia) {
            cerr << "Invalid argument: " << ia.what() << endl;
            e_flag = true;
        }

        flag = isProperOutputDimSetting(output_dim);
        if (!flag) {
            if (!e_flag)
                cerr << "Error: <" << output_dim << "> is not a valid size of the output layer!" << endl;

            if (++err_num >= 3)
                return false;
        }
        e_flag = false;
        cerr.flush();
    } while (!flag);


    cout << "Which network generation mode would you like?" << endl
    << "Automatic or Threshold? (A/T) ";
    cin >> mode_str;
    mode = getNetworkModeSetting(mode_str);
    if ( mode == THRESHOLD ) {
        int percent;

        err_num = 0;
        do {
            percent = getThresholdPercentage();
            if ( percent < 0 ) {
                flag = false;

                if (++err_num >= 3)
                    return false;
            } else
                flag = true;
        } while ( !flag );

        setThresholdPercent(percent);
    }

    setNumConvolutionLayers(num_conv);
    setConvolutionFilterSize(conv_filter_size);
    setNumFullyConnectedLayers(num_fc);
    setOutputDimension(output_dim);
    setNetworkMode(mode);

    return true;
}

bool UserInput::getPrototxt() {
    string prototxt;
    cout << "Would you like to generate a prototxt at the end? (Y/N) ";
    cin >> prototxt;

    return strcasecmp("Y", prototxt.c_str()) == 0;
}

int UserInput::getThresholdPercentage() {
    string threshold_str;
    int threshold;
    cout << "What percentage of the input would you like to downsample to? ";
    cin >> threshold_str;
    try {
        threshold = stoi(threshold_str, nullptr, 10);
    } catch (const std::invalid_argument &ia) {
        cerr << "Invalid argument: " << ia.what() << endl;
        cerr.flush();
        return -1;
    }

    return threshold;
}

void UserInput::setInputFilename(std::string filename) {
    this->mInputFilename = filename;
}

void UserInput::setInputDimensions(int size, int num_channels, int num_input) {
    this->mInputHeight = size;
    this->mInputWidth = size;
    this->mNumInputChannels = num_channels;
    this->mNumberInput = num_input;
}

void UserInput::setBatchSize(int batch_size) {
    LayerBase::setBatchSize(batch_size);
}

void UserInput::setNumConvolutionLayers(int num_convolution) {
    this->mNumConvLayers = num_convolution;
}

void UserInput::setConvolutionFilterSize(int conv_filter_size) {
    this->mConvFilterSize = conv_filter_size;
}

void UserInput::setNumFullyConnectedLayers(int num_fullyconn) {
    this->mNumFullyConnLayers = num_fullyconn;
}

void UserInput::setOutputDimension(int output_dim) {
    this->mOutputDim = output_dim;
}

void UserInput::setNetworkMode(NetworkMode network_mode) {
    this->mNetworkMode = network_mode;
}

void UserInput::setThresholdPercent(int threshold_percent) {
    this->mThresholdPercent = threshold_percent;
}

std::string UserInput::getInputFilename() {
    if ( mHasInputFilename )
        return this->mInputFilename;
    else
        return "generated_network.prototxt";
}

int UserInput::getInputWidth() {
    return this->mInputWidth;
}

int UserInput::getInputHeight() {
    return this->mInputHeight;
}

int UserInput::getNumInputChannels() {
    return this->mNumInputChannels;
}

int UserInput::getNumConvLayers() {
    return this->mNumConvLayers;
}

int UserInput::getConvFilterSize() {
    return this->mConvFilterSize;
}

int UserInput::getNumFullyConnLayers() {
    return this->mNumFullyConnLayers;
}

int UserInput::getOutputDim() {
    return this->mOutputDim;
}

NetworkMode UserInput::getNetworkMode() {
    return this->mNetworkMode;
}

int UserInput::getThreshold() {
    return this->mThresholdPercent;
}

std::string UserInput::getNetworkName() {
    if ( mHasNetworkName )
        return this->mNetworkName;
    else
        return "generated_network";
}

int UserInput::getNumberInput() {
    return this->mNumberInput;
}

bool isProperNumberInput(int num_input) {
    return num_input >= 1;
}

bool isPowerOfTwo(int num) {
    bool flag = ((num != 0) && ((num & (~num + 1)) == num));
    return flag && (num > 16); // limit input size to powers of 2 greater than 16 for now
}

// todo: check against input file?
// todo: no way to verify until we open the file, i guess?
bool isProperNumChannels(int num_channels) {
    return num_channels >= 1;
}

bool isProperBatchSize(int batch_size) {
    return batch_size >= 1;
}

bool isProperConvSetting(int num_conv) {
    return num_conv >= 0;
}

bool isProperFullyConnectedSetting(int num_fc) {
    return num_fc >= 1;
}

bool isProperOutputDimSetting(int output_dim) {
    return output_dim >= 1;
}

NetworkMode getNetworkModeSetting(string mode_str) {
    if ( strcasecmp(mode_str.c_str(), "T") == 0 )
        return THRESHOLD;

    return AUTOMATIC;
}
