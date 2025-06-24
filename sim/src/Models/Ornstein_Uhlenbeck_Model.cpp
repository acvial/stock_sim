#include <Ornstein_Uhlenbeck_Model.h>

OrnsteinUhlenbeckModel::OrnsteinUhlenbeckModel(const ModelData& modelData, std::unique_ptr<JumpInterface> jumpModel_) : 
    Model             (modelData, std::move(jumpModel_)), 
    meanReversionSpeed(modelData.reversionSpeed        )
{}

double OrnsteinUhlenbeckModel::mu(double price_t, double time){

    (void) time;
    return meanReversionSpeed * (drift - price_t);
}

ModelData OrnsteinUhlenbeckModel::getModelData() const {

    return ModelData(drift, volatility, initialPrice, meanReversionSpeed);
}

double OrnsteinUhlenbeckModel::sigma(double price_t, double time){

    (void) time;
    (void) price_t;
    return volatility;
}