set(ENVIRONMENT_SOURCES 

    "/app/src/Environment_Manager/Environment_Manager.cpp"
)

set(ENVIRONMENT_INCLUDES 

    "/app/src/Environment_Manager/"
)

add_library               (ENVIRONMENT_LIB STATIC ${ENVIRONMENT_SOURCES})
target_include_directories(ENVIRONMENT_LIB PUBLIC ${ENVIRONMENT_INCLUDES})