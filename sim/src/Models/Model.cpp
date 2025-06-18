#include <Model.h>

Model::Model(){}

Model::Model(double drift_, double volatility_, double initialPrice_) : 
    drift       (drift_       ), 
    volatility  (volatility_  ), 
    initialPrice(initialPrice_)
{}

Model::Model(const ModelData& modelData){

    drift        = modelData.drift;
    volatility   = modelData.volatility;
    initialPrice = modelData.initialPrice;
}

Model::Model(const Model& other) :
    drift       ( other.drift      ),
    volatility  ( other.volatility ),
    initialPrice(other.initialPrice)
{}

Model& Model::operator=(const Model& other){

    if(this != &other){

        drift        = other.drift;
        volatility   = other.volatility;
        initialPrice = other.initialPrice;
    }

    return *this;
}

void Model::setDrift(double drift_){

    drift = drift_;
}

void Model::setVolatility(double volatility_){

    volatility = volatility_;
}

void Model::setInitialPrice(double initialPrice_){

    initialPrice = initialPrice_;
}

double Model::getDrift() const {

    return drift;
}

double Model::getVolatility() const {

    return volatility;
}

double Model::getInitialPrice() const {

    return initialPrice;
}