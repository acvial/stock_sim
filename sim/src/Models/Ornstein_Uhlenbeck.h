#ifndef ORSNTEIN_UHLENBECK_H
#define ORSNTEIN_UHLENBECK_H

#include <Model.h>

class OrnsteinUhlenbeck : public Model{

    private:

    double meanReversionSpeed;

    public: 

    OrnsteinUhlenbeck(const ModelData& modelData);
    ~OrnsteinUhlenbeck() = default;

    public:

    ModelData getModelData() const override;

    double mu(double price_t, double time_t) override;
    double sigma(double price_t, double time_t) override;
};

#endif