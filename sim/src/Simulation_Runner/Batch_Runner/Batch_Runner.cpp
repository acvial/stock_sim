#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <Batch_Runner.h>

BatchRunner::BatchRunner(const BatchData& batchData) : 
    numberOfPaths(batchData.numberOfPaths),
    metrics      (batchData.numberOfPaths,
                  batchData.interval,
                  batchData.requestedMetrics)
{
    basicPaths.reserve(numberOfPaths);
    crossingPaths.reserve(numberOfPaths);
}

BatchRunner::BatchRunner(const BatchRunner& other) :
    numberOfPaths(other.numberOfPaths),
    metrics      (other.metrics      )
{

    basicPaths.reserve(numberOfPaths);
    crossingPaths.reserve(numberOfPaths);
}

BatchRunner& BatchRunner::operator=(const BatchRunner& other){

    if(this != &other){

        numberOfPaths  = other.numberOfPaths;
        metrics        = other.metrics;
        basicPaths     = other.basicPaths;
        crossingPaths  = other.crossingPaths;
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

const std::vector<std::vector<double>>* BatchRunner::getBasicPaths() const {

    return &basicPaths;
}

const std::vector<std::vector<double>>* BatchRunner::getCrossingPaths() const {

    return &crossingPaths;
}

void BatchRunner::computePaths(std::unique_ptr<Model> model, std::unique_ptr<Integrator> integrator){

    // Integrate requested number of paths
    for(size_t k = 0; k < numberOfPaths; k++){

        SPDLOG_INFO("Integrating path: {}", k + 1);

        // Integrate one path (BASIC) and save it
        basicPaths.push_back(
            *std::move(
                integrator->integratePath(model->getModelData())
            )
        );

        if(metrics.getRequestedMetrics()->meanCrossingTime){

            // Integrate one path (CROSSING) and save it
           crossingPaths.push_back(
               *std::move(
                    integrator->integratePath(model->getModelData(), *metrics.getInterval())
                )
            );
        }

        // Refresh seed
        integrator->refreshSeed();
    }

    // Pass object reference to metrics object
    metrics.setBasicPaths(basicPaths);
    metrics.setCrossingPaths(crossingPaths);
}
