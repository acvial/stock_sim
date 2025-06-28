list(APPEND CMAKE_PREFIX_PATH "/usr/lib/cmake/Catch2")
find_package(Catch2 REQUIRED)

set(SUBDIRECTORIES 

    "/app/tests/unit/Model"
)

foreach(subdir ${SUBDIRECTORIES})
    add_subdirectory(${subdir})
endforeach()

