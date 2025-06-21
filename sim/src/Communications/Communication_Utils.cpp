#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <cstdlib>
#include <Communication_Utils.h>
#include <Logger.h>
#include <Environment_Manager.h>

zmq::context_t CommunicationUtils::pullContext = zmq::context_t(4);
zmq::context_t CommunicationUtils::pushContext = zmq::context_t(4);
zmq::socket_t CommunicationUtils::pullSocket = zmq::socket_t(CommunicationUtils::pullContext, ZMQ_PULL);
zmq::socket_t CommunicationUtils::pushSocket = zmq::socket_t(CommunicationUtils::pushContext, ZMQ_PUSH);

CommunicationUtils::CommunicationUtils(){

    // Pull address
    auto pullAddress = "tcp://" + std::string(EnvironmentManager::getEnv("CONTROLLER_NAME")) + ":" + EnvironmentManager::getEnv("IN_PORT");
    SPDLOG_DEBUG("Receiving address: {}", pullAddress);
    pullSocket.bind(pullAddress);

    // Push address
    auto pushAddress = "tcp://" + std::string(EnvironmentManager::getEnv("CONTROLLER_NAME")) + ":" + EnvironmentManager::getEnv("OUT_PORT");
    SPDLOG_DEBUG("Sending address: {}", pushAddress);
    pushSocket.connect(pushAddress);
}

CommunicationUtils::~CommunicationUtils(){

    pullSocket.close();
    pushSocket.close();

    pullContext.shutdown();
    pullContext.close();

    pushContext.shutdown();
    pushContext.close();
}

std::string CommunicationUtils::pull(){

    // Create empty string
    std::string serializedData;

    try{

        SPDLOG_DEBUG("Working...");

        while(true){

            zmq::message_t serializedMessage;
            std::optional<size_t> recvResult = pullSocket.recv(serializedMessage, zmq::recv_flags::dontwait);

            if(recvResult){ // If there is a message

                SPDLOG_ERROR("Received message.");
                serializedData = std::string(static_cast<char*>(serializedMessage.data()), serializedMessage.size());

                return serializedData;
            }
           else{ // Otherwise sleep for 0.1 seconds
                
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }
    catch(const zmq::error_t& e){

        SPDLOG_ERROR(e.what());

        // Terminate program
        std::terminate();
    }

    return serializedData;
}

void CommunicationUtils::push(std::string serializedData){

    // Send message
    zmq::message_t message(serializedData.size());
    memcpy(message.data(), serializedData.data(), serializedData.size());
    pushSocket.send(message, zmq::send_flags::none);
    SPDLOG_ERROR("Message sent");
}

protocols::SimulationRequest* CommunicationUtils::deserialize(std::string deserializeData){

    // Extract message and deserialise it
    protocols::SimulationRequest* simRequest = new protocols::SimulationRequest();
    if(!simRequest->ParseFromString(deserializeData)){

        throw std::runtime_error("Message deserialisation failed.");
    }

    // Print content only in debug mode
    if(Logger::getLogger()->should_log(spdlog::level::debug)){

        SPDLOG_DEBUG("###### MESSAGE CONTENT ######");
        printData(simRequest->DebugString());
    }

    return simRequest;
}

void CommunicationUtils::printData(std::string debugString){

    std::istringstream stream(debugString);
    std::string line;

    while(std::getline(stream, line)){

        SPDLOG_DEBUG("{}", line);
    }
}
