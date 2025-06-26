set(TEST_MODEL_SOURCES
    "/app/tests/unit/Model/test_model.cpp"
)

set(TEST_MODEL_INCLUDES 

    "/usr/include/"
    "/app/src/Model/"
)

set(TEST_MODEL_LIBRARIES 

    "/usr/lib/x86_64-linux-gnu/libfmt.so"
    "/usr/lib/libCatch2.a"
    MODEL_LIB
)

include_directories(${MODEL_LIB_INCLUDE_DIRS})

add_executable            (U_MODEL_TEST        ${TEST_MODEL_SOURCES})
target_include_directories(U_MODEL_TEST PUBLIC ${TEST_MODEL_INCLUDES})
target_link_libraries     (U_MODEL_TEST PUBLIC ${TEST_MODEL_LIBRARIES})

add_test(
    NAME    U_MODEL_TEST
    COMMAND U_MODEL_TEST
)