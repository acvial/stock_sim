#ifndef REQUESTED_METRICS_H
#define REQUESTED_METRICS_H

struct RequestedMetrics{

    bool meanCrossingTime;
    /// TODO: more metrics

    RequestedMetrics() = default;
    RequestedMetrics(bool meanCrossingTime_) :
        meanCrossingTime(meanCrossingTime_)
    {}
    ~RequestedMetrics() = default;
};

#endif