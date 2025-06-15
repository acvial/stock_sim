add_executable(Simulator main.cpp)

set(SUBDIRECTORIES 

    "/app/src/Communications/"
    "/app/src/Logger/"
    "/app/src/Manager/"
    "/app/src/Protocols/"
)

foreach(subdir ${SUBDIRECTORIES})
    add_subdirectory(${subdir})
endforeach()

set(LIBRARIES

    COMMUNICATIONS_LIB
    LOGGER_LIB
    PROTOCOL_LIB
)

target_link_libraries(Simulator ${LIBRARIES})