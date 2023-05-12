cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_analogmux4 LANGUAGES MikroC)
else()
    project(example_analogmux4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_analogmux4
        example/main.c

)


############################ example_analogmux4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_analogmux4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_analogmux4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_analogmux4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_analogmux4)
target_link_libraries(example_analogmux4 PUBLIC Click.AnalogMUX4)
############################ example_analogmux4 GENERATED CODE END ###########################
