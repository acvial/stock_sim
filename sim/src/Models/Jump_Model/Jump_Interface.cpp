#include <Jump_Interface.h>

JumpInterface::JumpInterface() :
    meanJumpIntensity(0.0),
    stdJumpIntensity(0.0),
    jumpFrequency(0.0),
    jumpType(NOT_SET)
{}

double JumpInterface::getJumpFrequency() const {

    return jumpFrequency;
}

double JumpInterface::getMeanJumpIntensity() const {

    return meanJumpIntensity;
}

double JumpInterface::getStdJumpIntensity() const {

    return stdJumpIntensity;
}

int JumpInterface::getJumpMechanism() const {

    return jumpType;
}