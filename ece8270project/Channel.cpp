//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#include "Channel.h"

Channel::Channel(ChannelType channel_type) {
    mSize = 0;
    setChannelType(channel_type);
}

Channel::Channel(ChannelType channel_type, int size) {
    setChannelType(channel_type);
    setSize(size);
    mValues = new std::vector<uint8_t>(mSize);
}

Channel::Channel(ChannelType channel_type, std::vector<uint8_t> *values) {

}

Channel::~Channel() {
    delete mValues;
}

Channel* Channel::getChannel() {
    return this;
}

std::string Channel::getChannelType() {
    switch ( mChannelType ) {
        case GRAYSCALE:
            return "greyscale";

        case RED:
            return "red";

        case GREEN:
            return "green";

        case BLUE:
            return "blue";

        case RGB:
            return "red / green / blue";

        default:
            return "greyscale";
    }
}
ChannelType Channel::getChannelTypeEnum() {
    return this->mChannelType;
}

void Channel::setChannelType(ChannelType channel_type) {
    this->mChannelType = channel_type;
}

std::vector<uint8_t>* Channel::getChannelValues() {
    return this->mValues;
}

void Channel::addChannelValues(std::vector<uint8_t> *values) {
    this->mValues = values;
}

int Channel::getSize() {
    return mSize;
}

void Channel::setSize(int size) {
    this->mSize = size;
    //todo: this is a bad idea
}

uint8_t Channel::getValueAtIndex(int index) {
    return mValues->at(index);
}

void Channel::setValueAtIndex(int index, uint8_t value) {
    mValues->emplace(mValues->begin() + index, value);
}

std::string Channel::toString() {
    std::stringstream ss;

    ss << "Channel Type: ";
    ss << getChannelType() << std::endl;


    return ss.str();
}
