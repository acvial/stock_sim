#ifndef JUMP_MODEL_H
#define JUMP_MODEL_H

#include <random>

#include <Jump_Data.h>
#include <Jump_Interface.h>

enum JumpMechanism{

    ADDITIVE,
    MULTIPLICATIVE,
};

template<typename Distribution>
class JumpModel : public JumpInterface{

    private:

    std::mt19937 rng;
    std::poisson_distribution<int> jumpFreqDist;
    Distribution jumpIntDist;

    double meanJumpIntensity;
    double jumpFrequency;
    JumpMechanism jumpType;

    public:

    JumpModel           () = default;
    JumpModel           (const JumpData&& jumpData, JumpMechanism jumpType_);
    JumpModel           (const JumpModel& other);
    JumpModel& operator=(const JumpModel& other);
    ~JumpModel          () = default;

    double operator*(double rhs) override;

    /// @brief Initialises Poisson and custom jump intensity distributions
    void createDistributions(std::mt19937& rng_, double timestp) override;
};

#include <Jump_Model.tpp>

#endif