#ifndef BATCH_RUNNER_H
#define BATCH_RUNNER_H

#include <cmath>
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
    std::vector<std::vector<double>> paths;

    public:

    BatchRunner           () = default;
    BatchRunner           (const BatchData& batchData);
    BatchRunner           (const BatchRunner& other);
    BatchRunner& operator=(const BatchRunner& other);
    ~BatchRunner          () = default;

    public:

    void setNumberOfPaths(uint numberOfPaths_);

    uint                                    getNumberOfPaths() const;
    Metrics*                                getMetrics      ();
    const std::vector<std::vector<double>>* getPaths        () const;

    /// @brief Calls integrator and model and generates a given number of paths.
    void computePaths(std::unique_ptr<Model> model, std::unique_ptr<Integrator> integrator);
};

#endif