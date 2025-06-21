#ifndef INTEGRATOR_FACTORY_H
#define INTEGRATOR_FACTORY_H

#include <memory>
#include <Integrator.h>
#include <Euler_Maruyama.h>

class IntegratorFactory{

    public: 
    
    IntegratorFactory() = default;
    ~IntegratorFactory() = default;

    /// @brief Created the correct derived instance of Integrator.
    /// @param type      String indicating the type of Integrator.
    /// @param IntegratorData Contruction parameters.
    /// @return Pointer to selected derived class.
    static std::unique_ptr<Integrator> create(const std::string type, const IntegrationData& IntegratorData);
};

#endif