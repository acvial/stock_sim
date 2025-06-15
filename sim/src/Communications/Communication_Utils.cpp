#include <cstdlib>

#include <Communication_Utils.h>


CommunicationUtils::CommunicationUtils() :
    pullContext(4), pullSocket(pullContext, ZMQ_PULL),
    pushContext(4), pushSocket(pushContext, ZMQ_PUSH){

    // Pull address
    auto pullAddress = "tcp://" + std::string(std::getenv("CONTROLLER_NAME")) + ":" + std::getenv("IN_PORT");
    pullSocket.bind(pullAddress);

    // Push address
    auto pushAddress = "tcp://" + std::string(std::getenv("CONTROLLER_NAME")) + ":" + std::getenv("OUT_PORT");
    pullSocket.bind(pushAddress);
}