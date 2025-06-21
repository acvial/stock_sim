#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <Euler_Maruyama.h>
#include <Logger.h>

EulerMaruyamaScheme::EulerMaruyamaScheme(const IntegrationData& integrationData) : Integrator(integrationData){}

std::unique_ptr<std::vector<double>> EulerMaruyamaScheme::integratePath(const ModelData& modelData){

    std::vector<double> path;

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
        SPDLOG_DEBUG("Iteration: {}", k + 1);
        SPDLOG_DEBUG("   Price {}", p_1);
    }

    return std::make_unique<std::vector<double>>(path);
}

std::unique_ptr<std::vector<double>> EulerMaruyamaScheme::integratePath(const ModelData& modelData, const std::pair<double, double>& interval){

    std::vector<double> path;

    // Unpack values
    double mu    = modelData.drift;
    double sigma = modelData.volatility;
    double p_0   = modelData.initialPrice;

    double p_1 = 0;

    bool isInInterval = true;
    int counter = 1;

    // Loop over number of steps
    while(isInInterval){

        // Calculate initial price of the next iteration
        p_1 = p_0 + mu * delta_t + sigma * dist(rng);
        p_0 = p_1;

        // Update path
        path.push_back(p_1);

        // Log results
        SPDLOG_DEBUG("Iteration: {}", counter);
        SPDLOG_DEBUG("   Price {}", p_1);

        // Check if is in interval
        isInInterval = ((interval.first <= p_1) && (p_1 <= interval.second));

        // Update counter
        counter += 1;
    }

    return std::make_unique<std::vector<double>>(path);
}