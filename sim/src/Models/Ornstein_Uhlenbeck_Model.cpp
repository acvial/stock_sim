#include <Ornstein_Uhlenbeck_Model.h>

OrnsteinUhlenbeckModel::OrnsteinUhlenbeckModel(const ModelData& modelData) : 
    Model             (modelData               ), 
    meanReversionSpeed(modelData.reversionSpeed)
{}

double OrnsteinUhlenbeckModel::mu(double price_t, double time_t){

    (void) time_t;
    return meanReversionSpeed * (drift - price_t);
}

ModelData OrnsteinUhlenbeckModel::getModelData() const {

    return ModelData(drift, volatility, initialPrice, meanReversionSpeed);
}

double OrnsteinUhlenbeckModel::sigma(double price_t, double time_t){

    (void) time_t;
    (void) price_t;
    return volatility;
}