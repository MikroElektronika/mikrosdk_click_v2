cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gainamp LANGUAGES MikroC)
else()
    project(example_gainamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gainamp
        example/main.c

)


############################ example_gainamp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gainamp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gainamp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gainamp PUBLIC MikroSDK.Log)
add_subdirectory(lib_gainamp)
target_link_libraries(example_gainamp PUBLIC Click.GainAMP)
############################ example_gainamp GENERATED CODE END ###########################
