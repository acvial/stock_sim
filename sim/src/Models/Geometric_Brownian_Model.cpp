#include <Geometric_Brownian_Model.h>

GeometricBrownianModel::GeometricBrownianModel(const ModelData& modelData, std::unique_ptr<JumpInterface> jumpModel_) : 
    Model(modelData, std::move(jumpModel_)){}

double GeometricBrownianModel::mu(double price_t, double time){

    (void) time;
    return drift * price_t;
}

double GeometricBrownianModel::sigma(double price_t, double time){

    (void) time;
    return volatility * price_t;
}