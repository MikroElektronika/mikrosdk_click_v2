cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lriot LANGUAGES MikroC)
else()
    project(example_lriot LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lriot
        example/main.c

)


############################ example_lriot GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lriot PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lriot PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lriot PUBLIC MikroSDK.Log)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_lriot PUBLIC MikroSDK.Conversions)
add_subdirectory(lib_lriot)
target_link_libraries(example_lriot PUBLIC Click.LRIoT)
############################ example_lriot GENERATED CODE END ###########################
