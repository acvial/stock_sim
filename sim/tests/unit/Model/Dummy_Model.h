#ifndef DUMMY_MODEL_H
#define DUMMY_MODEL_H

#include <Model.h>

class DummyModel : public Model {

    public:

    DummyModel() : Model(){};
    DummyModel(
        double drift_, 
        double volatility_, 
        double initialPrice_) : Model(drift_, volatility_, initialPrice_, nullptr){}
    DummyModel(const ModelData& modelData) : Model(modelData, nullptr){};
    ~DummyModel() = default;

    ModelData getModelData() const override {

        return ModelData(
            drift,
            volatility,
            initialPrice,
            0
        );
    };

    double mu(double price_t, double time) const override {

        (void) price_t;
        (void) time;
        return 0;
    }

    double sigma(double price_t, double time) const override {

        (void) price_t;
        (void) time;
        return 0;
    }
};

#endif