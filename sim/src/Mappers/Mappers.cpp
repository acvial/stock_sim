#include <Mappers.h>

std::unique_ptr<Model> Mapper::mapModel(protocols::SimulationRequest* deserialisedMessage){

    // Extract model data parameters
    const auto& parameters = deserialisedMessage->parameters();

    const ModelData modelData(
        parameters.drift(),
        parameters.volatility(),
        parameters.initial_price()
    );

    // Extract type of model
    const std::string type = deserialisedMessage->ModelType_Name(deserialisedMessage->model());

    // Call model factory
    return ModelFactory::create(type, modelData);
}

std::unique_ptr<Integrator> Mapper::mapIntegrator(protocols::SimulationRequest* deserialisedMessage){

    // Extract integrator data parameters
    const auto& integrator = deserialisedMessage->integration();

    const IntegrationData integrationData(
        integrator.timestep(),
        integrator.time_horizon()
    );

    // Extract type of scheme
    const std::string type = integrator.Scheme_Name(integrator.scheme());

    // Call integrator factory
    return IntegratorFactory::create(type, integrationData);
}

std::unique_ptr<BatchRunner> Mapper::mapBatchConfig(protocols::BatchConfig* batchConfig){

    // Map requested metrics
    RequestedMetrics requestedMetrics(batchConfig->mean_crossing_time());

    // Map interval
    std::pair<double, double> interval;

    if(batchConfig->has_interval()){

        const auto& protoInterval = batchConfig->interval();
        interval = std::make_pair<double, double>(protoInterval.a(), protoInterval.b());
    }

    BatchData batchData(batchConfig->num_paths(),
                        requestedMetrics,
                        interval);
    
    return std::make_unique<BatchRunner>(batchData);
}

void Mapper::setLogLevel(protocols::LogConfig* logConfig){

    // Set corresponding log level
    switch(logConfig->level()){

        case(protocols::LogConfig::DEBUG): {

            spdlog::set_level(spdlog::level::debug);
            break;
        }
        case(protocols::LogConfig::INFO): {

            spdlog::set_level(spdlog::level::info);
            break;
        }
        case(protocols::LogConfig::ERROR): {

            spdlog::set_level(spdlog::level::err);
            break;
        }
        default: {

            throw std::invalid_argument("Requested unknown log level.");
        }
    }
}

protocols::BatchResult* Mapper::mapBatchResults(Metrics* metrics){

    // Create pointer
    protocols::BatchResult* batchResults = new protocols::BatchResult();

    // Map variance and expectation paths
    const std::vector<double>* expectation = metrics->getExpectedPath();
    const std::vector<double>* variance    = metrics->getVariancePath();

    for(size_t k = 0; k < metrics->getNumberOfPaths(); k++){

        batchResults->add_expected_path(expectation->at(k));
        batchResults->add_variance_path(variance->at(k));
    }

    // Map crossing time
    if(metrics->getRequestedMetrics()->meanCrossingTime){

        mapMeanCrossingTime(batchResults->mutable_crossing_results(), metrics->getMeanCrossingTime());
    }

    return batchResults;
}

void Mapper::mapMeanCrossingTime(protocols::MeanCrossingResults* protoCrossingResults, const MeanCrossingTime* meanCrossingTime){

    // Set data
    protoCrossingResults->set_expected_crossing_price  (meanCrossingTime->meanPrice             );
    protoCrossingResults->set_expected_crossing_time   (meanCrossingTime->meanTime              );
    protoCrossingResults->set_number_of_above_crossings(meanCrossingTime->numberOfAboveCrossings);
    protoCrossingResults->set_number_of_below_crossings(meanCrossingTime->numberOfBelowCrossings);
}