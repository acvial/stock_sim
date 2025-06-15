set(LOGGER_SOURCES

    "/app/src/Logger/Logger.cpp"
)

set(LOGGER_INCLUDES

    "/usr/include"
    "/app/src/Logger"
)

set(LOGGER_LIBRARIES

    "/usr/lib/x86-64-linux-gnu/libfmt.so"
)

add_library               (LOGGER_LIB STATIC ${LOGGER_SOURCES})
target_include_directories(LOGGER_LIB PUBLIC ${LOGGER_INCLUDES})
target_link_libraries     (LOGGER_LIB PUBLIC ${LOGGER_LIBRARIES})