#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include <Integrator.h>

Integrator::Integrator() :
    delta_t    (0),
    timeHorizon(0){

    reservePathMemory();
    initialiseRandomEngine();
}

Integrator::Integrator(double timestep, double timeHorizon_) : 
    delta_t    (timestep    ),
    timeHorizon(timeHorizon_)
{
    reservePathMemory();
    initialiseRandomEngine();
}

Integrator::Integrator(const IntegrationData& integrationData){

    delta_t     = integrationData.delta_t;
    timeHorizon = integrationData.timeHorizon;

    reservePathMemory();
    initialiseRandomEngine();
}

Integrator::Integrator(const Integrator& other) : 
    delta_t    (other.delta_t    ),
    timeHorizon(other.timeHorizon)
{
    reservePathMemory();
    initialiseRandomEngine();
}

Integrator& Integrator::operator=(const Integrator& other){

    if(this != &other){

        delta_t     = other.delta_t;
        timeHorizon = other.timeHorizon;
    }

    return *this;
}

void Integrator::setTimestep(double timestep){

    delta_t = timestep;
}

double Integrator::getTimestep() const {

    return delta_t;
}

uint Integrator::getNumSteps() const {

    return numSteps;
}

const std::vector<double>* Integrator::getPath() const {

    return &path;
}

void Integrator::reservePathMemory(){

    numSteps = (uint) std::ceil(timeHorizon / delta_t);
    path.reserve(numSteps);
}

void Integrator::initialiseRandomEngine(){

    // Seed
    std::random_device rd;
    rng = std::mt19937(rd());

    // Engine
    dist = std::normal_distribution(0.0, delta_t);
}

void Integrator::refreshSeed(){

    auto timeSeed = static_cast<uint>(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    // Memory address as simple entropy usiing XOR
    auto entropyMix = reinterpret_cast<uintptr_t>(this); 
    rng = std::mt19937(static_cast<uint>(timeSeed ^ entropyMix));
}