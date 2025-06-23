#ifndef JUMP_INTERFACE_H
#define JUMP_INTERFACE_H

class JumpInterface{

    /// @brief Define an operator * to be able to aplly a sum or a multiplication.
    /// @param rhs 
    /// @return 
    virtual double operator*(double rhs) = 0;

    /// @brief Initialises Poisson and custom jump intensity distributions
    virtual void createDistributions(std::mt19937& rng_, double timestp);
};

#endif