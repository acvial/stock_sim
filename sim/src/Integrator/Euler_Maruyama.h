#ifndef EULER_MARUYAMA_H
#define EULER_MARUYAMA_H

#include <Integrator.h>

class EulerMaruyamaScheme : public Integrator{

    public:

    EulerMaruyamaScheme(const IntegrationData& other);
    ~EulerMaruyamaScheme() = default;

    public:

    /// @brief Calculates the path. Stop condition: time horizon reached.
    /// @param modelData SDE parameters at given time.
    /// @return Pointer to path.
    std::unique_ptr<std::vector<double>> integratePath(const ModelData& modelData) override;

    /// @brief Calculates the path. Stop condition. price scpated interval.
    /// @param modelData SDE parameters at given time.
    /// @param interval Price interval.
    /// @return Pointer to path.
    std::unique_ptr<std::vector<double>> integratePath(const ModelData& modelData, const std::pair<double, double>& interval) override;
};

#endif