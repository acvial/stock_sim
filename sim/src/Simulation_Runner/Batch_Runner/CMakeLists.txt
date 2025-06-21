set(BATCH_RUNNER_SOURCES

    "/app/src/Simulation_Runner/Batch_Runner/Batch_Runner.cpp"
    "/app/src/Simulation_Runner/Batch_Runner/Metrics/Metrics.cpp"
)

set(BATCH_RUNNER_INCLUDES

    "/app/src/Simulation_Runner/Batch_Runner/"
    "/app/src/Simulation_Runner/Batch_Runner/Metrics/"
    "/app/src/Models"
    "/app/src/Integrator"
    "/app/src/Logger"
)

set(BATCH_RUNNER_LIBRARIES

    "/usr/lib/x86_64-linux-gnu/libfmt.so"
    MODEL_LIB 
    INTEGRATOR_LIB
)

add_library               (BATCH_RUNNER_LIB STATIC ${BATCH_RUNNER_SOURCES})
target_include_directories(BATCH_RUNNER_LIB PUBLIC ${BATCH_RUNNER_INCLUDES})
target_link_libraries     (BATCH_RUNNER_LIB PUBLIC ${BATCH_RUNNER_LIBRARIES})