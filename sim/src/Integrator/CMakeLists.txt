set(INTEGRATOR_SOURCES

    "/app/src/Integrator/Integrator.cpp"
    "/app/src/Integrator/Euler_Maruyama.cpp"
    "/app/src/Integrator/Integrator_Factory.cpp"
)

set(INTEGRATOR_INCLUDES

    "/app/src/Logger"
    "/app/src/Integrator"
    "/app/src/Models"
)

set(INTEGRATOR_LIBRARIES

    MODEL_LIB
    "/usr/lib/x86_64-linux-gnu/libfmt.so"
)

add_library               (INTEGRATOR_LIB STATIC ${INTEGRATOR_SOURCES})
target_include_directories(INTEGRATOR_LIB PUBLIC ${INTEGRATOR_INCLUDES})
target_link_libraries     (INTEGRATOR_LIB PUBLIC ${INTEGRATOR_LIBRARIES})