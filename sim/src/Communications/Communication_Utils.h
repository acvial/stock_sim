#include <zmq.hpp>
#include <Simulation.pb.h>

#ifndef COMMUNICATION_UTILS_H
#define COMMUNICATION_UTILS_H

class CommunicationUtils{

    private:

    zmq::socket_t  pushSocket, pullSocket;
    zmq::context_t pushContext, pullContext;

    public:

    CommunicationUtils();
    ~CommunicationUtils();

    private:

    /// @brief Sends a message.
    /// @param serializedData 
    void push(std::string serializedData);

    /// @brief Receives a message.
    /// @return Message content as string.
    std::string pull();

    /// @brief Deserialized data on string input.
    /// @param serializedData Serialized message.
    /// @return Simulation request protocol deserialized class.
    protocols::SimulationRequest* deserialize(std::string serializedData);

    /// @brief Prints protobuf message using spdlog.
    /// @param debugString 
    void printData(std::string debugString);
};

#endif