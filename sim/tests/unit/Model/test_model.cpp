#include <catch2/catch_all.hpp>

#include <Model_Factory.h>
#include <Jump_Model.h>
#include <Dummy_Model.h>
#include <Dummy_Distribution.h>

TEST_CASE("Model"){

    ModelData modelData(20, 0.5, 100.0, 1);

    SECTION("Basic"){

        // Constructors

        // Default
        std::unique_ptr<Model> model_d = std::make_unique<DummyModel>();
        CHECK(model_d->getDrift() == 0);
        CHECK(model_d->getVolatility() == 0);
        CHECK(model_d->getInitialPrice() == 0);

        // Custom: disperse data
        std::unique_ptr<Model> model_dd = std::make_unique<DummyModel>(
            modelData.drift,
            modelData.volatility,
            modelData.initialPrice
        );
        CHECK(model_dd->getDrift() == 20);
        CHECK(model_dd->getVolatility() == 0.5);
        CHECK(model_dd->getInitialPrice() == 100.0);

        // Custom: grouped data
        std::unique_ptr<Model> model_gd = std::make_unique<DummyModel>(modelData);
        CHECK(model_gd->getDrift() == 20);
        CHECK(model_gd->getVolatility() == 0.5);
        CHECK(model_gd->getInitialPrice() == 100.0);

        // Operator ==
        CHECK(*model_dd == *model_gd);

        // Check when unknown model
        CHECK_THROWS_AS(ModelFactory::create("", modelData, nullptr), std::invalid_argument);
    }

    SECTION("Geometric Brownian Motion"){

        // Call factory
        CHECK_NOTHROW(ModelFactory::create("GEOMETRIC_BROWNIAN_MOTION", modelData, nullptr));
        std::unique_ptr<Model> model = ModelFactory::create("GEOMETRIC_BROWNIAN_MOTION", modelData, nullptr);

        // Assert model parameters
        CHECK(model->mu((double) 50, 0) == 1000.0); // mu
        CHECK(model->sigma((double) 10, 0) == 5.0); // sigma
    }

    SECTION("Ornstein-Uhlenbeck"){

        // Call factory
        CHECK_NOTHROW(ModelFactory::create("ORNSTEIN_UHLENBECK", modelData, nullptr));
        std::unique_ptr<Model> model = ModelFactory::create("ORNSTEIN_UHLENBECK", modelData, nullptr);

        // Assert model parameters
        CHECK(model->mu((double) 50, 0) == -30.0); // mu
        CHECK(model->sigma((double) 10, 0) == 0.5); // sigma
    }
}

TEST_CASE("Jump Model"){

    JumpData jumpData(20, 3.0, 3.0);
    std::random_device rd;
    std::mt19937 rng = std::mt19937(rd());

    SECTION("Basic"){

        // Constructors

        // Default
        JumpModel<DummyDistribution> jumpModel_d;
        CHECK(jumpModel_d.getJumpFrequency() == 0.0);
        CHECK(jumpModel_d.getMeanJumpIntensity() == 0.0);
        CHECK(jumpModel_d.getStdJumpIntensity() == 0.0);
        CHECK(jumpModel_d.getJumpMechanism() == 0);

        // Custom
        JumpModel<DummyDistribution> jumpModel_c(jumpData, JumpMechanism::ADDITIVE);
        CHECK(jumpModel_c.getJumpFrequency() == 20.0);
        CHECK(jumpModel_c.getMeanJumpIntensity() == 3.0);
        CHECK(jumpModel_c.getStdJumpIntensity() == 3.0);
        CHECK(jumpModel_c.getJumpMechanism() == 1);
    }

    SECTION("Jump Mechanism"){

        // Uniform-Possion
        std::unique_ptr<JumpInterface> jump_A = std::make_unique<JumpModel<std::uniform_real_distribution<double>>>(jumpData, ADDITIVE);
        std::unique_ptr<JumpInterface> jump_M = std::make_unique<JumpModel<std::uniform_real_distribution<double>>>(jumpData, MULTIPLICATIVE);
        std::unique_ptr<JumpInterface> jump_NS = std::make_unique<JumpModel<std::uniform_real_distribution<double>>>(jumpData, NOT_SET);

        // Create distributions
        jump_A->createDistributions(rng, 1);
        jump_M->createDistributions(rng, 1);
        jump_NS->createDistributions(rng, 1);

        // Get number of jumps
        auto poissDist = std::poisson_distribution<int>(jump_A->getJumpFrequency());
        int numJumps = poissDist(rng);

        // Get jump intensity
        auto uniDist = std::uniform_real_distribution<double>(3.0, 3.0);
        double jumpInt = uniDist(rng);

        // Check additive and multiplicative behaviour. Rememeber RNG is shared.
        double number = 1;
        CHECK((*jump_A) * number == jumpInt * numJumps + number);
        CHECK((*jump_M) * number == std::pow((jumpInt - 1), numJumps) * number);
        CHECK_THROWS_AS((*jump_NS) * number, std::invalid_argument);
    }
}