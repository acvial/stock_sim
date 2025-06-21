#ifndef BATCH_DATA_H
#define BATCH_DATA_H

#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>

#include <Requested_Metrics.h>

struct BatchData{

    uint numberOfPaths;
    RequestedMetrics requestedMetrics;
    std::pair<double, double> interval;

    BatchData() = default;
    BatchData(uint numberOfPaths_,
              RequestedMetrics requestedMetrics_,
              std::pair<double, double> interval_
    ){
        numberOfPaths    = numberOfPaths_;
        requestedMetrics = requestedMetrics_;
        interval         = interval_;
    }
    ~BatchData() = default;
};

#endif