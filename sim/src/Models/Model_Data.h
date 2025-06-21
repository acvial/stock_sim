#ifndef MODEL_DATA_H
#define MODEL_DATA_H

struct ModelData{

    ModelData() = default;
    ModelData(double drift_, double volatility_, double initialPrice_){
        drift        = drift_;
        volatility   = volatility_;
        initialPrice = initialPrice_;
    }
    ~ModelData() = default;

    double drift;
    double volatility;
    double initialPrice;
};

#endif