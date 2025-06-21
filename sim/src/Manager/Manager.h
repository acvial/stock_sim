#ifndef MANAGER_H
#define MANAGER_H

#include <Logger.h>
#include <Communication_Utils.h>
#include <Simulation.pb.h>
#include <Mappers.h>
#include <Batch_Runner.h>

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
};

#endif