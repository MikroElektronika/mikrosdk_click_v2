cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_volume LANGUAGES MikroC)
else()
    project(example_volume LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_volume
        example/main.c

)


############################ example_volume GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_volume PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_volume PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_volume PUBLIC MikroSDK.Log)
add_subdirectory(lib_volume)
target_link_libraries(example_volume PUBLIC Click.Volume)
############################ example_volume GENERATED CODE END ###########################
