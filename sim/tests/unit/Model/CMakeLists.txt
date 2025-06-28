set(TEST_MODEL_SOURCES

    "/app/tests/unit/Model/test_model.cpp"
    "/app/tests/unit/unit_tests_main.cpp"
)

set(TEST_MODEL_INCLUDES 

    "/usr/include/"
    "/app/src/Model/"
    "/app/tests/unit/Model/"
)

set(TEST_MODEL_LIBRARIES 

    "/usr/lib/x86_64-linux-gnu/libfmt.so"
    Catch2::Catch2WithMain
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