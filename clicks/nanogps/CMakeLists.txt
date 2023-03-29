cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_nanogps LANGUAGES MikroC)
else()
    project(example_nanogps LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_nanogps
        example/main.c

)


############################ example_nanogps GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_nanogps PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_nanogps PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_nanogps PUBLIC MikroSDK.Log)
add_subdirectory(lib_nanogps)
target_link_libraries(example_nanogps PUBLIC Click.Nanogps)
############################ example_nanogps GENERATED CODE END ###########################
