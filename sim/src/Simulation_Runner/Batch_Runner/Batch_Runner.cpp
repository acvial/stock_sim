#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <Batch_Runner.h>

BatchRunner::BatchRunner(const BatchData& batchData) : 
    numberOfPaths(batchData.numberOfPaths),
    metrics      (batchData.numberOfPaths,
                  batchData.interval,
                  batchData.requestedMetrics)
{
    paths.reserve(numberOfPaths);
}

BatchRunner::BatchRunner(const BatchRunner& other) :
    numberOfPaths(other.numberOfPaths),
    metrics      (other.metrics      )
{

    paths.reserve(numberOfPaths);
}

BatchRunner& BatchRunner::operator=(const BatchRunner& other){

    if(this != &other){

        numberOfPaths = other.numberOfPaths;
        metrics       = other.metrics;
        paths         = other.paths;
    }

    return *this;
}

void BatchRunner::setNumberOfPaths(uint numberOfPaths_){

    numberOfPaths = numberOfPaths_;
}

uint BatchRunner::getNumberOfPaths() const {

    return numberOfPaths;
}

Metrics* BatchRunner::getMetrics(){

    return &metrics;
}

const std::vector<std::vector<double>>* BatchRunner::getPaths() const {

    return &paths;
}

void BatchRunner::computePaths(std::unique_ptr<Model> model, std::unique_ptr<Integrator> integrator){

    // Integrate requested number of paths
    for(size_t k = 0; k < numberOfPaths; k++){

        SPDLOG_INFO("Integrating path: {}", k + 1);

        // Integrate one path
        integrator->integratePath(model->getModelData());

        // Save path
        paths.push_back(*integrator->getPath());

        // Refresh seed
        integrator->refreshSeed();
    }

    // Pass object reference to metrics object
    metrics.setPaths(paths);
}