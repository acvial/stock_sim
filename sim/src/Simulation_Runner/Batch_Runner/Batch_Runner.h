#ifndef BATCH_RUNNER_H
#define BATCH_RUNNER_H

#include <random>
#include <cmath>
#include <memory>
#include <string>
#include <vector>

#include <Batch_Data.h>
#include <Metrics.h>
#include <Model.h>
#include <Integrator.h>
#include <Logger.h>

class BatchRunner{

    private:

    uint                             numberOfPaths;
    Metrics                          metrics;
    std::vector<std::vector<double>> basicPaths;
    std::vector<std::vector<double>> crossingPaths;

    std::unique_ptr<Model> model;
    std::unique_ptr<Integrator> integrator;

    std::mt19937 rng;
    std::normal_distribution<double> dist;

    public:

    BatchRunner           () = default;
    BatchRunner           (const BatchData& batchData);
    BatchRunner           (const BatchRunner& other);
    BatchRunner& operator=(const BatchRunner& other);
    ~BatchRunner          () = default;

    public:

    /// @brief Sets model and integrator data. Passes random seed to those objects.
    /// @param model      Model data.
    /// @param integrator Integrator data.
    void setIntegratorAndModel(std::unique_ptr<Model> model, std::unique_ptr<Integrator> integrator);

    void setNumberOfPaths(uint numberOfPaths_);

    uint                                    getNumberOfPaths() const;
    Metrics*                                getMetrics      ();
    const std::vector<std::vector<double>>* getBasicPaths   () const;
    const std::vector<std::vector<double>>* getCrossingPaths() const;

    /// @brief Clears paths from memory.
    void resetPaths();

    /// @brief Calls integrator and model and generates a given number of paths.
    void computePaths();

    public:

    /// @brief Created engine and seed.
    void initialiseRandomEngine();

    /// @brief Refreshes random seed using time and entropy.
    void refreshSeed();
};

#endif