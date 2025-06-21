#ifndef ENVIRONMENT_MANAGER_H
#define ENVIRONMENT_MANAGER_H

#include <string>
#include <cstdlib>

class EnvironmentManager{

    private:

    EnvironmentManager() = delete;
    ~EnvironmentManager() = default;

    public:

    /// @brief Safely returns an environment variable value.
    /// @param envName Name of the environment variable.
    /// @return Value of the environment variable.
    static std::string getEnv(const std::string& envName);
};

#endif