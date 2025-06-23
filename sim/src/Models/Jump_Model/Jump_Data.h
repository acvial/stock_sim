#ifndef JUMP_DATA_H
#define JUMP_DATA_H

struct JumpData{

    double jumpFrequency;
    double meanJumpIntensity;

    JumpData() = default;
    JumpData(double jumpFrequency_, double meanJumpIntensity_){

        jumpFrequency     = jumpFrequency_;
        meanJumpIntensity = meanJumpIntensity_;
    }
    ~JumpData() = default;
};

#endif