#include <Jump_Model.h>

template <typename Distribution>
JumpModel<Distribution>::JumpModel(const JumpData& jumpData, JumpMechanism jumpType_, std::mt19937& rng_) :
    jumpFrequency    (jumpData.jumpFrequency    ),
    meanJumpIntensity(jumpData.meanJumpIntensity),
    jumpType         (jumpType_                 ),
    rng              (rng_                      )
{}

template <typename Distribution>
JumpModel<Distribution>::JumpModel(const JumpModel& other) :
    jumpFrequency    (other.jumpFrequency    ),
    meanJumpIntensity(other.meanJumpIntensity),
    jumpType         (other.jumpType         ),
    rng              (other.rng              )
{}

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
double JumpModel<Distribution>::operator*(double rhs){

    double result = rhs;

    // Compute number of jumps
    int numberOfJumps = jumpFreqDist(rng);

    if(jumpType == ADDITIVE){

        for(int k = 0; k < numberOfJumps, k++){

            result += jumpIntDist(rng);
        }
    }
    else if(jumpType == MULTIPLICATIVE){

        for(int k = 0; k < numberOfJumps, k++){

            result *= jumpIntDist(rng) - 1;
        }
    }

    return result;
}

template <typename Distribution>
double operator*(double lhs, const JumpModel<Distribution>& rhs){

    double result = lhs;

    // Compute number of jumps
    int numberOfJumps = jumpFreqDist(rhs.rng);

    if(rhs.jumpType == ADDITIVE){

        for(int k = 0; k < numberOfJumps, k++){

            result += rhs.jumpIntDist(rhs.rng);
        }
    }
    else if(rhs.jumpType == MULTIPLICATIVE){

        for(int k = 0; k < numberOfJumps, k++){

            result *= rhs.jumpIntDist(rhs.rng) - 1;
        }
    }

    return result;
}

template <typename Distribution>
void JumpModel<Distribution>::createDistributions(std::mt19937& rng_, double timestep){

    rng = rng_;
    jumpFreqDist = std::poisson_distribution<int>(jumpFrequency * timestep);
    jumpIntDist  = Distribution(meanJumpIntensity);
}