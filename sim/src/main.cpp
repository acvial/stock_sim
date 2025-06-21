#include <Logger.h>
#include <Manager.h>
#include <Environment_Manager.h>

int main(){

    // Create an instance of manager
    Manager& manager = Manager::getManager();
    
    // Initialise the logger
    std::string logName = EnvironmentManager::getEnv("LOG_FILE_PATH");
    std::string pattern = "[%Y-%m-%d %H:%M:%S.%f] [%s] [%!] [%#] [%^%l%$] %v";
    
    auto logger = Logger::initialiseLogger(logName, pattern);
    
    if(!logger){
    
        spdlog::error("Failed to initialise the logger.");
        std::terminate();
    }
    
    // Set default level
    spdlog::set_level(spdlog::level::debug);
    
    std::string logLevel;
    
    if(logger->should_log(spdlog::level::debug)){
    
        logLevel = "DEBUG";
    }
    else if(logger->should_log(spdlog::level::info)){
    
        logLevel = "INFO";
    }
    else if(logger->should_log(spdlog::level::err)){
    
        logLevel = "ERROR";
    }
    
    SPDLOG_ERROR("Initial log level is {}.", logLevel);
    
    // Run simulation
    manager.runSimulation();
}
