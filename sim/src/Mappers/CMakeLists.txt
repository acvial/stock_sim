set(MAPPER_SOURCES

    "/app/src/Mappers/Mappers.cpp"
)

set(MAPPER_INCLUDES

    "/app/src/Integrator/"
    "/app/src/Logger/"
    "/app/src/Mappers/"
    "/app/src/Models/"
    "/app/src/Protocols/"
)

set(MAPPER_LIBRARIES

    LOGGER_LIB
    PROTOCOL_LIB
    MODEL_LIB 
    INTEGRATOR_LIB
    SIMULATOR_RUNNER_LIB
)

add_library               (MAPPER_LIB STATIC ${MAPPER_SOURCES})
target_include_directories(MAPPER_LIB PUBLIC ${MAPPER_INCLUDES})
target_link_libraries     (MAPPER_LIB PUBLIC ${MAPPER_LIBRARIES})