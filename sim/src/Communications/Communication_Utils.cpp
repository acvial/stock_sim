#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <cstdlib>
#include <Communication_Utils.h>
#include <Logger.h>

CommunicationUtils::CommunicationUtils() :
    pullContext(4), pullSocket(pullContext, ZMQ_PULL),
    pushContext(4), pushSocket(pushContext, ZMQ_PUSH){

    // Pull address
    auto pullAddress = "tcp://" + std::string(std::getenv("CONTROLLER_NAME")) + ":" + std::getenv("IN_PORT");
    SPDLOG_DEBUG("Receiving address: {}", pullAddress);
    pullSocket.bind(pullAddress);

    // Push address
    auto pushAddress = "tcp://" + std::string(std::getenv("CONTROLLER_NAME")) + ":" + std::getenv("OUT_PORT");
    SPDLOG_DEBUG("Sending address: {}", pushAddress);
    pullSocket.bind(pushAddress);
}

CommunicationUtils::~CommunicationUtils(){

    pullSocket.close();
    pushSocket.close();

    pullContext.shutdown();
    pullContext.close();

    pushContext.shutdown();
    pushContext.close();
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
}

void CommunicationUtils::printData(std::string debugString){

    std::istringstream stream(debugString);
    std::string line;

    while(std::getline(stream, line)){

        SPDLOG_DEBUG("{}", line);
    }
}
