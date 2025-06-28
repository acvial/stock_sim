#include <Model.h>

Model::Model() :
    drift(0),
    volatility(0),
    initialPrice(0)
{
    jumpModel = nullptr;
}

Model::Model(double drift_, double volatility_, double initialPrice_, std::unique_ptr<JumpInterface> jumpModel_) : 
    drift       (drift_               ), 
    volatility  (volatility_          ), 
    initialPrice(initialPrice_        ),
    jumpModel   (std::move(jumpModel_))
{}

Model::Model(const ModelData& modelData, std::unique_ptr<JumpInterface> jumpModel_) : jumpModel   (std::move(jumpModel_)){

    drift        = modelData.drift;
    volatility   = modelData.volatility;
    initialPrice = modelData.initialPrice;
}

Model::Model(const Model& other) :
    drift       ( other.drift              ),
    volatility  ( other.volatility         ),
    initialPrice(other.initialPrice        )
{}

Model& Model::operator=(const Model& other){

    if(this != &other){

        drift        = other.drift;
        volatility   = other.volatility;
        initialPrice = other.initialPrice;
        jumpModel    = other.jumpModel->clone();
    }

    return *this;
}

bool Model::operator==(const Model& other){
    
    bool isEqual = (drift         == other.drift        &&
                    volatility    == other.volatility   &&
                    initialPrice  == other.initialPrice
                );

    if((jumpModel != nullptr) && (other.jumpModel != nullptr)){

        isEqual = (isEqual && *jumpModel == *other.jumpModel);
    }
    else{

        isEqual = (isEqual && jumpModel == other.jumpModel);
    }

    return isEqual;
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

void Model::setModelData(const ModelData& modelData_){

    drift        = modelData_.drift;
    volatility   = modelData_.volatility;
    initialPrice = modelData_.initialPrice;
}

void Model::setJumpModel(std::unique_ptr<JumpInterface> jumpModel_){

    jumpModel = std::move(jumpModel_);
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

ModelData Model::getModelData() const {

    return ModelData(drift, volatility, initialPrice, 0);
}

JumpInterface* Model::getJumpModel() const {

    return jumpModel.get();
}