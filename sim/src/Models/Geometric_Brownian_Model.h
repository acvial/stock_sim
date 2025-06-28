#ifndef BROWNIAN_MOTION_MODEL_H
#define BROWNIAN_MOTION_MODEL_H

#include <Model.h>

class GeometricBrownianModel: public Model{

    public: 

    GeometricBrownianModel(const ModelData& modelData, std::unique_ptr<JumpInterface> jumpModel_);
    ~GeometricBrownianModel() = default;

    public:

    double mu(double price_t, double time_t) const override;
    double sigma(double price_t, double time_t) const override;
};

#endif