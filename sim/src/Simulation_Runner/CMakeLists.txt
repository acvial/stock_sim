add_subdirectory(Batch_Runner)

set(SIMULATOR_RUNNER_LIBRARIES 

    BATCH_RUNNER_LIB
    # INTERACTIVE_RUNNER_LIB
)

add_library          (SIMULATOR_RUNNER_LIB INTERFACE)
target_link_libraries(SIMULATOR_RUNNER_LIB INTERFACE ${SIMULATOR_RUNNER_LIBRARIES})