#ifndef ORSNTEIN_UHLENBECK_MODEL_H
#define ORSNTEIN_UHLENBECK_MODEL_H

#include <Model.h>

class OrnsteinUhlenbeckModel : public Model{

    private:

    double meanReversionSpeed;

    public: 

    OrnsteinUhlenbeckModel(const ModelData& modelData, std::unique_ptr<JumpInterface> jumpModel_);
    bool operator==(const OrnsteinUhlenbeckModel& other);
    ~OrnsteinUhlenbeckModel() = default;

    public:

    ModelData getModelData() const override;

    double mu(double price_t, double time_t) const override;
    double sigma(double price_t, double time_t) const override;
};

#endif