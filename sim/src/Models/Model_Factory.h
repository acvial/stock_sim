#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include <memory>
#include <Model.h>
#include <Geometric_Brownian_Model.h>
#include <Ornstein_Uhlenbeck_Model.h>

class ModelFactory{

    public: 
    
    ModelFactory() = default;
    ~ModelFactory() = default;

    /// @brief Created the correct derived instance of model.
    /// @param type      String indicating the type of model.
    /// @param modelData Contruction parameters.
    /// @return Pointer to selected derived class.
    static std::unique_ptr<Model> create(const std::string type, const ModelData& modelData);
};

#endif