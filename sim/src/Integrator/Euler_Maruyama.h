#ifndef EULER_MARUYAMA_H
#define EULER_MARUYAMA_H

#include <Integrator.h>

class EulerMaruyamaScheme : public Integrator{

    public:

    EulerMaruyamaScheme(const IntegrationData& other);
    ~EulerMaruyamaScheme() = default;

    public:

    /// @brief Compute the next point of the path.
    /// @param modelData SDE parameters.
    /// @param p_0       Price of the stock at last timestep.
    /// @return Value of the price on next timestep.
    double computeOneTimestep(const ModelData& modelData, double p_0) override;

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