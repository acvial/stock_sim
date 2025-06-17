#include <Model.h>

Model::Model(){}

Model::Model(float drift_, float volatility_, float initialPrice_) : 
    drift(drift_), 
    volatility(volatility_), 
    initialPrice(initialPrice_)
{}

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

void Model::setDrift(float drift_){

    drift = drift_;
}

void Model::setVolatility(float volatility_){

    volatility = volatility_;
}

void Model::setInitialPrice(float initialPrice_){

    initialPrice = initialPrice_;
}

float Model::getDrift() const {

    return drift;
}

float Model::getVolatility() const {

    return volatility;
}

float Model::getInitialPrice() const {

    return initialPrice;
}