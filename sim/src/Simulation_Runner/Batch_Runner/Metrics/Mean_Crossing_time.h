#ifndef MEAN_CROSSING_TIME_H
#define MEAN_CROSSING_TIME_H

#include <cmath>

struct MeanCrossingTime{

    uint   numberOfTotalCrossings;
    uint   numberOfAboveCrossings;
    uint   numberOfBelowCrossings;
    double meanTime; 

    MeanCrossingTime() = default;
    MeanCrossingTime(uint   numberOfTotalCrossings_,
                     uint   numberOfAboveCrossings_,
                     uint   numberOfBelowCrossings_,
                     double meanTime_) : 
        numberOfTotalCrossings(numberOfTotalCrossings_),
        numberOfAboveCrossings(numberOfAboveCrossings_),
        numberOfBelowCrossings(numberOfBelowCrossings_),
        meanTime              (meanTime_              )
    {}
    ~MeanCrossingTime() = default;
};

#endif