set(MODEL_SOURCES

    "/app/src/Models/Model.cpp"
)

set(MODEL_INCLUDES

    "/app/src/Models"
)

set(MODEL_LIBRARIES

    "/usr/lib/x86-64-linux-gnu/libfmt.so"
)

add_library               (MODEL_LIB STATIC ${MODEL_SOURCES})
target_include_directories(MODEL_LIB PUBLIC ${MODEL_INCLUDES})
target_link_libraries     (MODEL_LIB PUBLIC ${MODEL_LIBRARIES})