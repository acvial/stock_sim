#ifndef INTEGRATION_DATA_H
#define INTEGRATION_DATA_H

struct IntegrationData{

    double delta_t;
    double timeHorizon;

    IntegrationData() = default;
    IntegrationData(double timestep, double timeHorizon_){

        delta_t     = timestep;
        timeHorizon = timeHorizon_;
    }
    ~IntegrationData() = default;
};

#endif