#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <Euler_Maruyama.h>
#include <Logger.h>

EulerMaruyamaScheme::EulerMaruyamaScheme(const IntegrationData& integrationData) : Integrator(integrationData){}

double EulerMaruyamaScheme::computeOneTimestep(Model* model, double p_0){

    // Unpack values
    double mu    = model->mu(p_0, delta_t);
    double sigma = model->sigma(p_0, delta_t);
    JumpInterface* jumpModel = model->getJumpModel();
    
    double p_1;

    // Calculate initial price of the next iteration
    p_1 = (*jumpModel) * (p_0 + mu * delta_t + sigma * dist(rng));

    return p_1;
}

std::unique_ptr<std::vector<double>> EulerMaruyamaScheme::integratePath(Model* model){

    std::vector<double> path;

    // Unpack values
    double p_0 = model->getInitialPrice();
    double p_1 = 0;

    // Loop over number of steps
    for(size_t k = 0; k < numSteps; k++){

        // Calculate initial price of the next iteration
        p_1 = computeOneTimestep(model, p_0);
        p_0 = p_1;

        // Update path
        path.push_back(p_1);

        // Log results
        SPDLOG_DEBUG("Iteration: {}", k + 1);
        SPDLOG_DEBUG("   Price {}", p_1);
    }

    return std::make_unique<std::vector<double>>(path);
}

std::unique_ptr<std::vector<double>> EulerMaruyamaScheme::integratePath(Model* model, const std::pair<double, double>& interval){

    std::vector<double> path;

    // Unpack values
    double p_0 = model->getInitialPrice();

    double p_1 = 0;

    bool isInInterval = true;
    int counter = 1;

    // Loop over number of steps
    while(isInInterval){

        // Calculate initial price of the next iteration
        p_1 = computeOneTimestep(model, p_0);
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