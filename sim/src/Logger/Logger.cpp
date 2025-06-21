#include <Logger.h>

std::shared_ptr<spdlog::logger> Logger::logger = nullptr;
bool Logger::hasBeenInitialised = false;

std::shared_ptr<spdlog::logger> Logger::initialiseLogger(std::string logName, std::string pattern){

    // Define sinks
    std::vector<spdlog::sink_ptr> sinks;

    // Console sink
    auto consoleSink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
    consoleSink->set_pattern(pattern);
    consoleSink->set_level(spdlog::level::trace);
    sinks.push_back(consoleSink);

    // File sink
    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logName, true);
    fileSink->set_pattern(pattern);
    fileSink->set_level(spdlog::level::trace);
    sinks.push_back(fileSink);

    logger = std::make_shared<spdlog::logger>("multi_sink", begin(sinks), end(sinks));
    spdlog::set_default_logger(logger);
    logger->set_level(spdlog::level::trace);

    spdlog::flush_on(spdlog::level::err);

    hasBeenInitialised = true;

    return logger;
}

std::shared_ptr<spdlog::logger> Logger::getLogger(){

    return hasBeenInitialised ? logger : nullptr;
}