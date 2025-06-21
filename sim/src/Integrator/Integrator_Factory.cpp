#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <Integrator_Factory.h>
#include <Logger.h>
#include <stdexcept>

std::unique_ptr<Integrator> IntegratorFactory::create(const std::string type, const IntegrationData& IntegratorData){

    std::unique_ptr<Integrator> integratorClass = nullptr;

    if(type == "EULER_MARUYAMA"){

        integratorClass = std::make_unique<EulerMaruyamaScheme>(IntegratorData);
        SPDLOG_INFO("Euler-Maruyama integrator created.");
    }
    else{

        throw std::invalid_argument("Invalid or unknown integrator.");
    }

    return integratorClass;
}