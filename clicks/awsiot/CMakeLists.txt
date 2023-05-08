cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_awsiot LANGUAGES MikroC)
else()
    project(example_awsiot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_awsiot
        example/main.c
    
)


############################ example_awsiot GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_awsiot PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_awsiot PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_awsiot PUBLIC MikroSDK.Log)
add_subdirectory(lib_awsiot)
target_link_libraries(example_awsiot PUBLIC Click.AWSIoT)
############################ example_awsiot GENERATED CODE END ###########################

