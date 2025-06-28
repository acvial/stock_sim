#ifndef JUMP_MODEL_H
#define JUMP_MODEL_H

#include <random>
#include <memory>

#include <Jump_Data.h>
#include <Jump_Interface.h>

template<typename Distribution>
class JumpModel : public JumpInterface{

    private:

    std::mt19937 rng;
    std::poisson_distribution<int> jumpFreqDist;
    Distribution jumpIntDist;

    public:

    JumpModel           ();
    JumpModel           (const JumpData&  jumpData, JumpMechanism jumpType_);
    JumpModel           (const JumpData&& jumpData, JumpMechanism jumpType_);
    JumpModel           (const JumpModel& other);
    JumpModel& operator=(const JumpModel& other);
    bool      operator==(const JumpInterface& other) override;
    ~JumpModel          () = default;

    const std::mt19937& getSeed() const override;

    /// @brief Define an operator * to be able to aplly a sum or a multiplication.
    /// @param rhs Number to apply operation.
    /// @return Value of the operation.
    double operator*(double rhs) override;

    /// @brief Returns a copy of the suitable derived class.
    /// @return Copy of the derived class.
    std::unique_ptr<JumpInterface> clone() const override;

    /// @brief Initialises Poisson and custom jump intensity distributions
    void createDistributions(std::mt19937& rng_, double timestp) override;
};

#include <Jump_Model.tpp>

#endif