set(COMMUNICATIONS_SOURCES

    "/app/src/Communications/Communication_Utils.cpp"
)

set(COMMUNICATIONS_INCLUDES

    "/usr/include"
    "/app/src/Communications"
    "/app/src/Logger"
    "/app/src/Protocols"
)

set(COMMUNICATIONS_LIBRARIES

    "/usr/lib/x86_64-linux-gnu/libzmq.so"
    "/usr/lib/x86_64-linux-gnu/libfmt.so"
    "/usr/lib/x86_64-linux-gnu/libprotobuf.so"
    LOGGER_LIB
)

add_library               (COMMUNICATIONS_LIB STATIC ${COMMUNICATIONS_SOURCES})
target_include_directories(COMMUNICATIONS_LIB PUBLIC ${COMMUNICATIONS_INCLUDES})
target_link_libraries     (COMMUNICATIONS_LIB PUBLIC ${COMMUNICATIONS_LIBRARIES})