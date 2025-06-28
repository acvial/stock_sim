#ifndef JUMP_DATA_H
#define JUMP_DATA_H

struct JumpData{

    double jumpFrequency;
    double meanJumpIntensity;
    double stdJumpIntensity;

    JumpData() = default;
    JumpData(double jumpFrequency_, double meanJumpIntensity_, double stdJumpIntensity_){

        jumpFrequency     = jumpFrequency_;
        meanJumpIntensity = meanJumpIntensity_;
        stdJumpIntensity  = stdJumpIntensity_;
    }
    ~JumpData() = default;
};

#endif