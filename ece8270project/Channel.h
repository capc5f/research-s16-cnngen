//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_CHANNEL_H
#define RESEARCHDNNGENERATOR_CHANNEL_H


#include <string>
#include <sstream>
#include <vector>

enum ChannelType {
    GRAYSCALE, RED, GREEN, BLUE, RGB
};

class Channel {
private:
    ChannelType mChannelType;
    std::vector<uint8_t> *mValues;
    int mSize = 0;

public:
    Channel(ChannelType channel_type);
    Channel(ChannelType channel_type, int size);
    Channel(ChannelType channel_type, std::vector <uint8_t> *values);
    ~Channel();
    Channel* getChannel();
    std::string getChannelType();
    ChannelType getChannelTypeEnum();
    void setChannelType(ChannelType channel_type);
    std::vector<uint8_t>* getChannelValues();
    void addChannelValues(std::vector <uint8_t> *values);
    int getSize();
    void setSize(int size);
    uint8_t getValueAtIndex(int index);
    void setValueAtIndex(int index, uint8_t value);
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_CHANNEL_H
