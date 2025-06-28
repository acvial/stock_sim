#ifndef JUMP_INTERFACE_H
#define JUMP_INTERFACE_H

#include <memory>
#include <random>

enum JumpMechanism{

    NOT_SET,
    ADDITIVE,
    MULTIPLICATIVE,
};

class JumpInterface{

    protected:

    double meanJumpIntensity;
    double stdJumpIntensity;
    double jumpFrequency;
    JumpMechanism jumpType;

    public:

    JumpInterface();
    ~JumpInterface() = default;

    public:

    double getMeanJumpIntensity() const;
    double getStdJumpIntensity () const;
    double getJumpFrequency    () const;
    int    getJumpMechanism    () const;

    virtual bool operator==(const JumpInterface& other) = 0;

    /// @brief Returns a copy of the suitable derived class.
    /// @return Copy of the derived class.
    virtual std::unique_ptr<JumpInterface> clone() const = 0;

    virtual const std::mt19937& getSeed() const = 0;

    /// @brief Define an operator * to be able to aplly a sum or a multiplication.
    /// @param rhs Number to apply operation.
    /// @return Value of the operation.
    virtual double operator*(double rhs) = 0;

    /// @brief Initialises Poisson and custom jump intensity distributions
    virtual void createDistributions(std::mt19937& rng_, double timestp) = 0;
};

#endif