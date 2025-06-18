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
                std::unique_ptr<Model> model = mapModel(deserialisedMessage);

                // Set log level
                setLogLevel(deserialisedMessage->mutable_logconfig());

                // Delete data
                delete deserialisedMessage;
            }
            catch(const std::runtime_error& e){

                // Deserialize throws
                SPDLOG_ERROR(e.what());
                continue;
            }
            catch(const std::invalid_argument& e){

                // mapModel throws
                SPDLOG_ERROR(e.what());

                delete deserialisedMessage;
                continue;
            }
        }
    }
}

std::unique_ptr<Model> Manager::mapModel(protocols::SimulationRequest* deserialisedMessage){

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

void Manager::setLogLevel(protocols::LogConfig* logConfig){

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