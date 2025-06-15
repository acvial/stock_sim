#ifndef LOGGER_H
#define LOGGER_H

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/ansicolor_sink.h>

class Logger{

    private:

    static std::shared_ptr<spdlog::logger> logger;
    static bool hasBeenInitialised;

    public:

    /// @brief Initilises logger.
    /// @param logName Path to the log file.
    /// @param pattern Pattern of the logged data.
    /// @return Pointer to logger object.
    static std::shared_ptr<spdlog::logger> initialiseLogger(std::string logName, std::string pattern);

    /// @brief If initialised, calls logger.
    /// @return Logger object.
    static std::shared_ptr<spdlog::logger> getLogger();
};

#endif