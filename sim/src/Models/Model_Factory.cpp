#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <Model_Factory.h>
#include <Logger.h>
#include <stdexcept>

std::unique_ptr<Model> ModelFactory::create(const std::string type, const ModelData& modelData, std::unique_ptr<JumpInterface> jumpModel){

    std::unique_ptr<Model> modelClass = nullptr;

    if(type == "GEOMETRIC_BROWNIAN_MOTION"){

        modelClass = std::make_unique<GeometricBrownianModel>(modelData, std::move(jumpModel));
        SPDLOG_INFO("Geometric Brownian Motion model created.");
    }
    else if(type == "ORNSTEIN_UHLENBECK"){

        modelClass = std::make_unique<OrnsteinUhlenbeckModel>(modelData, std::move(jumpModel));
        SPDLOG_INFO("Ornstein-Uhlenbeck model created.");
    }
    else{

        throw std::invalid_argument("Invalid or unknown model.");
    }

    return modelClass;
}