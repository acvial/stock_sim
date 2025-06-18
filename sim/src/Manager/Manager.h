#ifndef MANAGER_H
#define MANAGER_H

#include <Logger.h>
#include <Communication_Utils.h>
#include <Model_Factory.h>
#include <Simulation.pb.h>

class Manager{

    private:

    Manager() = default;
    ~Manager() = default;

    public:

    Manager(const Manager& other) = delete;
    Manager& operator=(const Manager& other) = delete;

    /// @brief Accesses to the static manager instance.
    /// @return Static instance.
    static Manager& getManager();

    public:

    /// @brief Core function of the simulator. Establishes communications, maps protocol data and calls solver.
    void runSimulation();

    private:

    /// @brief Creates model class on protocol input.
    /// @param deserialisedMessage Protocol data.
    /// @return Pointer to suitable Model class.
    std::unique_ptr<Model> mapModel(protocols::SimulationRequest* deserialisedMessage);

    /// @brief Sets requested log level.
    /// @param deserialisedMessage Protocol data.
    void setLogLevel(protocols::LogConfig* logConfig);
};

#endif