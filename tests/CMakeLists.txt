project(pyUGFX_tests)

add_executable(pyUGFX_test1
    test1.cpp
)
target_link_libraries(pyUGFX_test1
    PRIVATE pyUGFX::library
)
if(${CMAKE_GENERATOR} MATCHES "Xcode")
    set_target_properties(pyUGFX_test1
        PROPERTIES 
            XCODE_GENERATE_SCHEME TRUE
            XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
    )
endif()