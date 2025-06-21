#ifndef METRICS_H
#define METRICS_H

#include <cmath>
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>

#include <Requested_Metrics.h>
#include <Mean_Crossing_time.h>
#include <Logger.h>

class Metrics{

    private:

    std::vector<double>              expectation, variance;
    MeanCrossingTime                 meanCrossingTime;
    uint                             numberOfPaths;
    std::pair<double, double>        interval;
    RequestedMetrics                 requestedMetrics;
    std::vector<std::vector<double>> paths;

    public:

    Metrics           () = default;
    Metrics           (uint                             numberOfPaths_,
                       const std::pair<double, double>& interval_,
                       const RequestedMetrics&          requestedMetrics_);
    Metrics           (const Metrics& other);
    Metrics& operator=(const Metrics& other);
    ~Metrics          () = default;

    void setPaths(std::vector<std::vector<double>>& paths_);

    /// @brief Checks which metrics have been requested and computes it.
    void computeMetrics(double timestep);

    /// @brief Computes expectation and variance. In batch mode these metrics are always calculated.
    void computeExpecteationAndVariance();

    /// @brief Computes the expected time that the price scapes the interval [a, b]
    void computeMeanCrossingTime(double timestep);

    /// TODO: More metrics
};

#endif