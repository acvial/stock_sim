#ifndef EULER_MARUYAMA_H
#define EULER_MARUYAMA_H

#include <Integrator.h>

class EulerMaruyamaScheme : public Integrator{

    public:

    EulerMaruyamaScheme(const IntegrationData& other);
    ~EulerMaruyamaScheme() = default;

    public:

    /// @brief Calculates the path.
    /// @param modelData SDE parameters at given time.
    void integratePath(const ModelData& modelData) override;
};

#endif