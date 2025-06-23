#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <random>
#include <vector>
#include <memory>
#include <cmath>
#include <chrono>

#include <Model_Data.h>
#include <Integration_Data.h>

class Integrator{

    protected:

    double delta_t;
    double timeHorizon;
    uint numSteps;

    std::mt19937 rng;
    std::normal_distribution<double> dist;

    public:

    Integrator           ();
    Integrator           (double timestep, double timeHorizon);
    Integrator           (const IntegrationData& other);
    Integrator           (const Integrator& other);
    Integrator& operator=(const Integrator& other);
    ~Integrator          () = default;

    public:

    void setTimestep(double delta_t_);
    void setSeed(std::mt19937& rng_);

    double getTimestep() const;
    uint   getNumSteps() const;

    /// @brief Compute the next point of the path.
    /// @param modelData SDE parameters.
    /// @param p_0       Price of the stock at last timestep.
    /// @return Value of the price on next timestep.
    virtual double computeOneTimestep(const ModelData& modelData, double p_0) = 0;

    /// @brief Calculates the path. Stop condition: time horizon reached.
    /// @param modelData SDE parameters at given time.
    /// @return Pointer to path.
    virtual std::unique_ptr<std::vector<double>> integratePath(const ModelData& modelData) = 0;

    /// @brief Calculates the path. Stop condition: price scpated interval.
    /// @param modelData SDE parameters at given time.
    /// @param interval Price interval.
    /// @return Pointer to path.
    virtual std::unique_ptr<std::vector<double>> integratePath(const ModelData& modelData, const std::pair<double, double>& interval) = 0;

    /// @brief Generates normal distribution with class' seed.
    void createDistribution();
};

#endif