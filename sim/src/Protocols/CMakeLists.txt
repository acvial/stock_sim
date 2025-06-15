set(PROTOCOL_SOURCES

    "/app/src/Protocols/Simulation.pb.cc"
)

set(PROTOCOL_INCLUDES

    "/usr/include"
    "/app/src/Protocols"
)

set(LOGGER_LIBRARIES

    "/usr/lib/x86-64-linux-gnu/libprotobuf.so"
)

add_library               (PROTOCOL_LIB STATIC ${PROTOCOL_SOURCES})
target_include_directories(PROTOCOL_LIB PUBLIC ${PROTOCOL_INCLUDES})
target_link_libraries     (PROTOCOL_LIB PUBLIC ${PROTOCOL_LIBRARIES})