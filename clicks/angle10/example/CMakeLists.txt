cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_angle10 LANGUAGES MikroC)
else()
    project(example_angle10 LANGUAGES C ASM)
endif()

add_executable(example_angle10
        main.c
    
)


############################ example_angle10 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_angle10 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_angle10 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_angle10 PUBLIC MikroSDK.Log)
add_subdirectory(lib_angle10)
target_link_libraries(example_angle10 PUBLIC Click.Angle10)
############################ example_angle10 GENERATED CODE END ###########################
