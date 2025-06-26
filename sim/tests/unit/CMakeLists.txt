set(SUBDIRECTORIES 

    "/app/tests/unit/Model"
)

foreach(subdir ${SUBDIRECTORIES})
    add_subdirectory(${subdir})
endforeach()
