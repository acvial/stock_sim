#ifndef MEAN_CROSSING_TIME_H
#define MEAN_CROSSING_TIME_H

#include <cmath>

struct MeanCrossingTime{

    uint   numberOfAboveCrossings;
    uint   numberOfBelowCrossings;
    double meanTime; 
    double meanPrice;

    MeanCrossingTime() = default;
    MeanCrossingTime(uint   numberOfAboveCrossings_,
                     uint   numberOfBelowCrossings_,
                     double meanTime_,
                     double meanPrice_) : 
        numberOfAboveCrossings(numberOfAboveCrossings_),
        numberOfBelowCrossings(numberOfBelowCrossings_),
        meanTime              (meanTime_              ),
        meanPrice             (meanPrice_             )
    {}
    ~MeanCrossingTime() = default;
};

#endif