add_executable(Simulator main.cpp)

set(SUBDIRECTORIES 

    "/app/src/Communications/"
    "/app/src/Logger/"
    "/app/src/Manager/"
    "/app/src/Protocols/"
    "/app/src/Models/"
)

foreach(subdir ${SUBDIRECTORIES})
    add_subdirectory(${subdir})
endforeach()

set(LIBRARIES

    MANAGER_LIB
)

target_link_libraries(Simulator ${LIBRARIES})