project(pyUGFX_tests)

add_executable(pyUGFX_test1
    test1.cpp
)

target_link_libraries(pyUGFX_test1
    PRIVATE pyUGFX::library
)