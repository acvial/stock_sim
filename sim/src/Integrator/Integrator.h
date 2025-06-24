#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <random>
#include <vector>
#include <memory>
#include <cmath>
#include <chrono>

#include <Model.h>
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

    double getTimestep() const;
    uint   getNumSteps() const;

    /// @brief Compute the next point of the path.
    /// @param model SDE parameters.
    /// @param p_0   Price of the stock at last timestep.
    /// @return Value of the price on next timestep.
    virtual double computeOneTimestep(Model* model, double p_0) = 0;

    /// @brief Calculates the path. Stop condition: time horizon reached.
    /// @param model SDE parameters at given time.
    /// @return Pointer to path.
    virtual std::unique_ptr<std::vector<double>> integratePath(Model* model) = 0;

    /// @brief Calculates the path. Stop condition: price scpated interval.
    /// @param model    SDE parameters at given time.
    /// @param interval Price interval.
    /// @return Pointer to path.
    virtual std::unique_ptr<std::vector<double>> integratePath(Model* model, const std::pair<double, double>& interval) = 0;

    /// @brief Generates normal distribution with class' seed.
    void createDistribution(std::mt19937& rng);
};

#endif