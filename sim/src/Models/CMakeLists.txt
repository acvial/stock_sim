set(MODEL_SOURCES

    "/app/src/Models/Model.cpp"
    "/app/src/Models/Geometric_Brownian_Model.cpp"
    "/app/src/Models/Ornstein_Uhlenbeck_Model.cpp"
    "/app/src/Models/Model_Factory.cpp"
    "/app/src/Models/Jump_Model/Jump_Model.tpp"
)

set(MODEL_INCLUDES

    "/app/src/Logger"
    "/app/src/Models"
    "/app/src/Models/Jump_Model"
)

set(MODEL_LIBRARIES

    "/usr/lib/x86_64-linux-gnu/libfmt.so"
)

add_library               (MODEL_LIB STATIC ${MODEL_SOURCES})
target_include_directories(MODEL_LIB PUBLIC ${MODEL_INCLUDES})
target_link_libraries     (MODEL_LIB PUBLIC ${MODEL_LIBRARIES})