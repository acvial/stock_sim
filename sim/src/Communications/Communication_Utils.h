#ifndef COMMUNICATION_UTILS_H
#define COMMUNICATION_UTILS_H

#include <zmq.hpp>
#include <Simulation.pb.h>

class CommunicationUtils{

    private:

    static zmq::socket_t  pushSocket, pullSocket;
    static zmq::context_t pushContext, pullContext;

    public:

    CommunicationUtils();
    ~CommunicationUtils();

    public:

    /// @brief Sends a message.
    /// @param serializedData 
    static void push(std::string serializedData);

    /// @brief Receives a message.
    /// @return Message content as string.
    static std::string pull();

    /// @brief Deserialized data on string input.
    /// @param serializedData Serialized message.
    /// @return Simulation request protocol deserialized class.
    static protocols::SimulationRequest* deserialize(std::string serializedData);

    private:

    /// @brief Prints protobuf message using spdlog.
    /// @param debugString 
    static void printData(std::string debugString);
};

#endif