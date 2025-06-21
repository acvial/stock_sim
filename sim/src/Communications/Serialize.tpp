#include <Communication_Utils.h>

template <typename ProtoData>
std::string CommunicationUtils::serialize(ProtoData* protoData){
    
    std::string serializedMessage;

    if(!protoData->SerializeToString(&serializedMessage)){

        throw std::runtime_error("Message serialization failed.");
    }

    return serializedMessage;
}