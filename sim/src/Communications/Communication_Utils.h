#include <zmq.hpp>

#ifndef COMMUNICATION_UTILS_H
#define COMMUNICATION_UTILS_H

class CommunicationUtils{

    private:

    zmq::socket_t  pushSocket, pullSocket;
    zmq::context_t pushContext, pullContext;

    public:

    CommunicationUtils();
    ~CommunicationUtils() = default;

    private:

    /// @brief Sends a message.
    /// @param serializedData 
    void push(std::string serializedData);

    /// @brief Receives a message.
    /// @return Message content as string.
    std::string pull();
};

#endif