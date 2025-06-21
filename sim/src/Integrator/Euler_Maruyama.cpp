#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <Euler_Maruyama.h>
#include <Logger.h>

EulerMaruyamaScheme::EulerMaruyamaScheme(const IntegrationData& integrationData) : Integrator(integrationData){}

void EulerMaruyamaScheme::integratePath(const ModelData& modelData){

    // Unpack values
    double mu    = modelData.drift;
    double sigma = modelData.volatility;
    double p_0   = modelData.initialPrice;

    double p_1 = 0;

    // Loop over number of steps
    for(size_t k = 0; k < numSteps; k++){

        // Calculate initial price of the next iteration
        p_1 = p_0 + mu * delta_t + sigma * dist(rng);
        p_0 = p_1;

        // Update path
        path.push_back(p_1);

        // Log results
        SPDLOG_INFO("Iteration: {}", k);
        SPDLOG_INFO("   Price {}", p_1);
    }
}