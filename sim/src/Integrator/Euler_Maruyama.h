#ifndef EULER_MARUYAMA_H
#define EULER_MARUYAMA_H

#include <Integrator.h>

class EulerMaruyamaScheme : public Integrator{

    public:

    EulerMaruyamaScheme(const IntegrationData& other);
    ~EulerMaruyamaScheme() = default;

    public:

    /// @brief Compute the next point of the path.
    /// @param model  SDE parameters.
    /// @param p_0    Price of the stock at last timestep.
    /// @return Value of the price on next timestep.
    double computeOneTimestep(Model* model, double p_0) override;

    /// @brief Calculates the path. Stop condition: time horizon reached.
    /// @param model SDE parameters at given time.
    /// @return Pointer to path.
    std::unique_ptr<std::vector<double>> integratePath(Model* model) override;

    /// @brief Calculates the path. Stop condition. price scpated interval.
    /// @param model SDE parameters at given time.
    /// @param interval Price interval.
    /// @return Pointer to path.
    std::unique_ptr<std::vector<double>> integratePath(Model* model, const std::pair<double, double>& interval) override;
};

#endif