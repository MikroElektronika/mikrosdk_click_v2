cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_relay LANGUAGES MikroC)
else()
    project(example_relay LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_relay
        example/main.c

)


############################ example_relay GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_relay PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_relay PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_relay PUBLIC MikroSDK.Log)
add_subdirectory(lib_relay)
target_link_libraries(example_relay PUBLIC Click.Relay)
############################ example_relay GENERATED CODE END ###########################
