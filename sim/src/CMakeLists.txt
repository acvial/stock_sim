add_executable(Simulator main.cpp)

set(SUBDIRECTORIES 

    "/app/src/Communications/"
    "/app/src/Integrator"
    "/app/src/Logger/"
    "/app/src/Manager/"
    "/app/src/Models/"
    "/app/src/Protocols/"
    "/app/src/Simulation_Runner/"
)

foreach(subdir ${SUBDIRECTORIES})
    add_subdirectory(${subdir})
endforeach()

set(LIBRARIES

    MANAGER_LIB
)

target_link_libraries(Simulator ${LIBRARIES})