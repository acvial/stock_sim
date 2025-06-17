#ifndef MANAGER_H
#define MANAGER_H

#include <Communication_Utils.h>
#include <Model.h>
#include <Simulation.pb.h>

class Manager{

    public:

    Manager() = delete;
    Manager operator=(Manager& other) = delete;

    private:

    /// @brief Core function of the simulator. Establishes communications, maps protocol data and calls solver.
    void run_simulation();


};

#endif