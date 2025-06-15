add_executable(Simulator main.cpp)

set(SUBDIRECTORIES 

    "/app/src/Logger/"
    "/app/src/Manager/"
)

foreach(subdir ${SUBDIRECTORIES})
    add_subdirectory(${subdir})
endforeach()

set(LIBRARIES

    LOGGER_LIB
)

target_link_libraries(Simulator ${LIBRARIES})