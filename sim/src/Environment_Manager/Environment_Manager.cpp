#include <stdexcept>
#include <Environment_Manager.h>

std::string EnvironmentManager::getEnv(const std::string& envName){

    auto envVal = getenv(envName.c_str());

    if(envVal == nullptr){

        throw std::runtime_error("Environment variable " + envName + "not found.");
    }

    return std::string(envVal);
}