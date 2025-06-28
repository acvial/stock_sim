#include <Ornstein_Uhlenbeck_Model.h>

OrnsteinUhlenbeckModel::OrnsteinUhlenbeckModel(const ModelData& modelData, std::unique_ptr<JumpInterface> jumpModel_) : 
    Model             (modelData, std::move(jumpModel_)), 
    meanReversionSpeed(modelData.reversionSpeed        )
{}

bool OrnsteinUhlenbeckModel::operator==(const OrnsteinUhlenbeckModel& other){

    return(
        drift              == other.getDrift       () &&
        volatility         == other.getVolatility  () &&
        initialPrice       == other.getInitialPrice() &&
        *jumpModel         == *other.getJumpModel  () &&
        meanReversionSpeed == other.meanReversionSpeed
    );
}

ModelData OrnsteinUhlenbeckModel::getModelData() const {

    return ModelData(drift, volatility, initialPrice, meanReversionSpeed);
}

double OrnsteinUhlenbeckModel::mu(double price_t, double time) const {

    (void) time;
    return meanReversionSpeed * (drift - price_t);
}

double OrnsteinUhlenbeckModel::sigma(double price_t, double time) const {

    (void) time;
    (void) price_t;
    return volatility;
}