#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <Metrics.h>

Metrics::Metrics(uint                             numberOfPaths_,
                 const std::pair<double, double>& interval_,
                 const RequestedMetrics&          requestedMetrics_) : 

    numberOfPaths(numberOfPaths_),
    interval     (interval_    ), 
    requestedMetrics (requestedMetrics_)
{}

Metrics::Metrics(const Metrics& other) : numberOfPaths(other.numberOfPaths), interval(other.interval), requestedMetrics(other.requestedMetrics){}

Metrics& Metrics::operator=(const Metrics& other){

    if(this != &other){

        numberOfPaths = other.numberOfPaths;
        interval      = other.interval;
        requestedMetrics  = other.requestedMetrics;
    }

    return *this;
}

void Metrics::setPaths(std::vector<std::vector<double>>& paths_){

    paths = paths_;
}

void Metrics::computeMetrics(double timestep){

    // Expectation and variance
    computeExpecteationAndVariance();

    // Mean crossing time
    if(requestedMetrics.meanCrossingTime){

        SPDLOG_INFO("Computing expected crossing time.");
        computeMeanCrossingTime(timestep);
    }
}

void Metrics::computeExpecteationAndVariance(){

    // Number of points
    size_t numberOfPoints = paths.at(0).size();

    // Compute individual metrics
    for(size_t k = 0; k < numberOfPoints; k++){

        double expect = 0;
        double var = 0;

        // Expectation
        SPDLOG_INFO("Computing expectation.");
        for(size_t j = 0; j < numberOfPaths; j++){

            expect += paths.at(j).at(k);

            if(j == numberOfPaths - 1){

                expectation.push_back(expect / numberOfPaths);
            }
        }

        // Variance
        SPDLOG_INFO("Computing variance.");
        for(size_t j = 0; j < numberOfPaths; j++){

            var += std::pow(paths.at(j).at(k) - expect / numberOfPaths, 2);

            if(j == numberOfPaths - 1){

                variance.push_back(var / numberOfPaths);
            }
        }
    }
}

void Metrics::computeMeanCrossingTime(double timestep){

    bool isAbove = false;
    bool isBelow = false;
    double meanTime = 0;
    uint totalNumberOfCrossings = 0;
    uint numberOfAboveCrossings = 0;
    uint numberOfBelowCrossings = 0;

    for(const auto& path : paths){

        for(size_t k = 0; k < path.size(); k++){

            // Get point
            double point = path.at(k);

            // Check whether the crossing has ocurred from above or below
            isBelow = (interval.first < point);
            isAbove = (point < interval.second);

            if(isAbove){

                SPDLOG_DEBUG("Path scaped interval from above.");

                // Update mean
                meanTime += (double) k;

                // Update counter
                totalNumberOfCrossings += 1;
                numberOfAboveCrossings += 1;

                break;
            }
            else if(isBelow){

                SPDLOG_DEBUG("Path scaped interval from below.");

                // Update mean
                meanTime += (double) k;

                // Update counter
                totalNumberOfCrossings += 1;
                numberOfBelowCrossings += 1;

                break;
            }
        }
    }

    // Store values
    meanCrossingTime = MeanCrossingTime(totalNumberOfCrossings,
                                        numberOfAboveCrossings,
                                        numberOfBelowCrossings,
                                        meanTime * timestep / totalNumberOfCrossings);
}