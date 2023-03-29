cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_leddriver LANGUAGES MikroC)
else()
    project(example_leddriver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_leddriver
        example/main.c

)


############################ example_leddriver GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_leddriver PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_leddriver PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_leddriver PUBLIC MikroSDK.Log)
add_subdirectory(lib_leddriver)
target_link_libraries(example_leddriver PUBLIC Click.LedDriver)
############################ example_leddriver GENERATED CODE END ###########################
