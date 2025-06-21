set(MANAGER_SOURCES

    "/app/src/Manager/Manager.cpp"
)

set(MANAGER_INCLUDES

    "/app/src/Communications/"
    "/app/src/Integrator/"
    "/app/src/Logger/"
    "/app/src/Manager/"
    "/app/src/Models/"
    "/app/src/Protocols/"
    "/app/src/Simulation_Runner/"
)

set(MANAGER_LIBRARIES

    COMMUNICATIONS_LIB
    PROTOCOL_LIB
    SIMULATOR_RUNNER_LIB
)

add_library               (MANAGER_LIB STATIC ${MANAGER_SOURCES})
target_include_directories(MANAGER_LIB PUBLIC ${MANAGER_INCLUDES})
target_link_libraries     (MANAGER_LIB PUBLIC ${MANAGER_LIBRARIES})