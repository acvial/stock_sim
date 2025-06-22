#include <Geometric_Brownian_Model.h>

GeometricBrownianModel::GeometricBrownianModel(const ModelData& modelData) : Model(modelData){}

double GeometricBrownianModel::mu(double price_t, double time_t){

    (void) time_t;
    return drift * price_t;
}

double GeometricBrownianModel::sigma(double price_t, double time_t){

    (void) time_t;
    return volatility * price_t;
}