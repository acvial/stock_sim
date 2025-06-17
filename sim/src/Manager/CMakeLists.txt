set(MANAGER_SOURCES

    "/app/src/Manager/Manager.cpp"
)

set(MANAGER_INCLUDES

    "/app/src/Communications/"
    "/app/src/Logger/"
    "/app/src/Manager/"
    "/app/src/Protocols/"
    "/app/src/Models/"
)

set(MANAGER_LIBRARIES

    COMMUNICATIONS_LIB
    LOGGER_LIB
    MODEL_LIB
    PROTOCOL_LIB
)

add_library               (MANAGER_LIB STATIC ${MANAGER_SOURCES})
target_include_directories(MANAGER_LIB PUBLIC ${MANAGER_INCLUDES})
target_link_libraries     (MANAGER_LIB PUBLIC ${MANAGER_LIBRARIES})