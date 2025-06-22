#include <Ornstein_Uhlenbeck.h>

OrnsteinUhlenbeck::OrnsteinUhlenbeck(const ModelData& modelData) : 
    Model             (modelData               ), 
    meanReversionSpeed(modelData.reversionSpeed)
{}

double OrnsteinUhlenbeck::mu(double price_t, double time_t){

    (void) time_t;
    return meanReversionSpeed * (drift - price_t);
}

ModelData OrnsteinUhlenbeck::getModelData() const {

    return ModelData(drift, volatility, initialPrice, meanReversionSpeed);
}

double OrnsteinUhlenbeck::sigma(double price_t, double time_t){

    (void) time_t;
    (void) price_t;
    return volatility;
}