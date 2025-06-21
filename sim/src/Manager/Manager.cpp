#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <thread>
#include <Manager.h>

Manager& Manager::getManager(){

    static Manager instance;

    return instance;
}

void Manager::runSimulation(){

    while(true){
        
        // Get serialized message
        std::string serializedData = CommunicationUtils::pull();

        if(serializedData.empty()){

            // If an empty message is received, sleep for 0.1 seconds and try again
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            SPDLOG_ERROR("Received an empty message.");
        }
        else{

            // Uninitialised pointer. No problem, never going to dereference it without being initilised later.
            protocols::SimulationRequest* deserialisedMessage;

            try{

                // Deserialise message
                deserialisedMessage = CommunicationUtils::deserialize(serializedData);

                // Get model
                std::unique_ptr<Model> model = Mapper::mapModel(deserialisedMessage);

                // Get integrator
                std::unique_ptr<Integrator> integrator = Mapper::mapIntegrator(deserialisedMessage);

                // Set log level
                Mapper::setLogLevel(deserialisedMessage->mutable_log_config());

                // Call simulator runner
                if(deserialisedMessage->mode() == protocols::SimulationRequest::BATCH){

                    // Get batch config
                    BatchRunner& batchRunner = *Mapper::mapBatchConfig(deserialisedMessage->mutable_batch_config());

                    // Run batch simulation
                    batchRunner.computePaths(std::move(model), std::move(integrator));

                    // Compute metrics
                    batchRunner.getMetrics()->computeMetrics(integrator->getTimestep());

                    // Map results
                    protocols::BatchResult* protoBatch = Mapper::mapBatchResults(batchRunner.getMetrics());

                    // Serialize data
                    std::string serializedMessage = CommunicationUtils::serialize<protocols::BatchResult>(protoBatch);

                    // Send results
                    CommunicationUtils::push(serializedMessage);
                }

                // Delete data
                delete deserialisedMessage;
            }
            catch(const std::runtime_error& e){

                // Deserialize throws
                SPDLOG_ERROR(e.what());
                continue;
            }
            catch(const std::invalid_argument& e){

                // Model, integration throws
                SPDLOG_ERROR(e.what());

                delete deserialisedMessage;
                continue;
            }
        }
    }
}

