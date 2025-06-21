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

void Metrics::setBasicPaths(std::vector<std::vector<double>>& basicPaths_){

    basicPaths = basicPaths_;
}

void Metrics::setCrossingPaths(std::vector<std::vector<double>>& crossingPaths_){

    crossingPaths = crossingPaths_;
}

uint Metrics::getNumberOfPaths() const {

    return numberOfPaths;
}

const std::vector<double>* Metrics::getExpectedPath() const {

    return &expectation;
}

const std::vector<double>* Metrics::getVariancePath() const {

    return &variance;
}

const MeanCrossingTime* Metrics::getMeanCrossingTime() const {

    return &meanCrossingTime;
}

const RequestedMetrics* Metrics::getRequestedMetrics() const {

    return &requestedMetrics;
}

const std::pair<double, double>* Metrics::getInterval() const {

    return &interval;
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
    size_t numberOfPoints = basicPaths.at(0).size();

    // Compute individual metrics
    for(size_t k = 0; k < numberOfPoints; k++){

        double expect = 0;
        double var = 0;

        // Expectation
        SPDLOG_INFO("Computing expectation.");
        for(size_t j = 0; j < numberOfPaths; j++){

            expect += basicPaths.at(j).at(k);

            if(j == numberOfPaths - 1){

                expectation.push_back(expect / numberOfPaths);
            }
        }

        // Variance
        SPDLOG_INFO("Computing variance.");
        for(size_t j = 0; j < numberOfPaths; j++){

            var += std::pow(basicPaths.at(j).at(k) - expect / numberOfPaths, 2);

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
    double meanPrice = 0;
    uint numberOfAboveCrossings = 0;
    uint numberOfBelowCrossings = 0;

    for(const auto& path : crossingPaths){

        // Compute mean time
        meanTime += (double) path.size();

        // Compute mean price
        double crossingPrice = path.back();
        meanPrice += crossingPrice;

        // Check whether the prices scaped the interval from above or below
        isAbove = (interval.second < crossingPrice);
        isBelow = (crossingPrice < interval.first);

        if(isAbove){ 

            numberOfAboveCrossings += 1; 
        }
        else if(isBelow){

            numberOfBelowCrossings += 1;
        }
        else{

            SPDLOG_ERROR("Path ended without crossing.");
        }
    }

    // Store values
    meanCrossingTime = MeanCrossingTime(numberOfAboveCrossings,
                                        numberOfBelowCrossings,
                                        meanTime * timestep / numberOfPaths,
                                        meanPrice / numberOfPaths);
}