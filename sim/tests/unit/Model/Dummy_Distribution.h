#include <random>

struct DummyDistribution{
    
    DummyDistribution(double = 0.0, double = 1.0) {}

    double operator()(std::mt19937&){

        return 1.0; 
    }
};