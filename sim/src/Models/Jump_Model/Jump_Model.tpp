#include <Jump_Model.h>

template<typename Distribution>
JumpModel<Distribution>::JumpModel() : JumpInterface(){}

template <typename Distribution>
JumpModel<Distribution>::JumpModel(const JumpData& jumpData, JumpMechanism jumpType_){

    meanJumpIntensity = jumpData.meanJumpIntensity;
    stdJumpIntensity  = jumpData.stdJumpIntensity;
    jumpFrequency     = jumpData.jumpFrequency;
    jumpType          = jumpType_;
}

template <typename Distribution>
JumpModel<Distribution>::JumpModel(const JumpData&& jumpData, JumpMechanism jumpType_){

    meanJumpIntensity = jumpData.meanJumpIntensity;
    stdJumpIntensity  = jumpData.stdJumpIntensity;
    jumpFrequency     = jumpData.jumpFrequency;
    jumpType          = jumpType_;
}

template <typename Distribution>
JumpModel<Distribution>::JumpModel(const JumpModel& other){

    meanJumpIntensity = other.meanJumpIntensity;
    stdJumpIntensity  = other.stdJumpIntensity ;
    jumpFrequency     = other.jumpFrequency;
    jumpType          = other.jumpType;
    rng               = other.rng;
}

template <typename Distribution>
JumpModel<Distribution>& JumpModel<Distribution>::operator=(const JumpModel& other){

    if(this != &other){

        jumpFrequency     = other.jumpFrequency;
        meanJumpIntensity = other.meanJumpIntensity;
        jumpType          = other.jumpType;
        rng               = other.rng;
    }

    return *this;
}

template <typename Distribution>
bool JumpModel<Distribution>::operator==(const JumpInterface& other){

    return(
        &rng              == &other.getSeed            () &&
        jumpFrequency     == other.getJumpFrequency    () &&
        meanJumpIntensity == other.getMeanJumpIntensity() &&
        stdJumpIntensity  == other.getStdJumpIntensity ()
    );
}

template <typename Distribution>
std::unique_ptr<JumpInterface> JumpModel<Distribution>::clone() const {

    return std::make_unique<JumpModel<Distribution>>(*this);
}

template <typename Distribution>
const std::mt19937& JumpModel<Distribution>::getSeed() const {

    return rng;
}

template <typename Distribution>
double JumpModel<Distribution>::operator*(double rhs){

    double result = rhs;

    // Compute number of jumps
    int numberOfJumps = jumpFreqDist(rng);

    if(jumpType == ADDITIVE){

        for(int k = 0; k < numberOfJumps; k++){

            result += jumpIntDist(rng);
        }
    }
    else if(jumpType == MULTIPLICATIVE){

        for(int k = 0; k < numberOfJumps; k++){

            result *= (jumpIntDist(rng) - 1);
        }
    }
    else{

        throw std::invalid_argument("Jump mechanism not set.");
    }

    return result;
}

template <typename Distribution>
void JumpModel<Distribution>::createDistributions(std::mt19937& rng_, double timestep){

    rng = rng_;
    jumpFreqDist = std::poisson_distribution<int>(jumpFrequency * timestep);
    jumpIntDist  = Distribution(meanJumpIntensity, stdJumpIntensity);
}