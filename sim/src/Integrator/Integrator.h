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
    std::vector<double> path;

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

    double                     getTimestep() const;
    uint                       getNumSteps() const;
    const std::vector<double>* getPath    () const;

    /// @brief Calculates the path.
    /// @param modelData SDE parameters at given time.
    virtual void integratePath(const ModelData& modelData) = 0;

    private:

    /// @brief Calculates number of steps and reserves memory for them.
    void reservePathMemory();

    /// @brief Created engine and seed.
    void initialiseRandomEngine();

    public:

    /// @brief Refreshes random seed using time and entropy.
    void refreshSeed();
};

#endif