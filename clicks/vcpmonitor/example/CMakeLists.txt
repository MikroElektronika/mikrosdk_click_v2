cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_vcpmonitor LANGUAGES MikroC)
else()
    project(example_vcpmonitor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_vcpmonitor
        main.c

)


############################ example_vcpmonitor GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_vcpmonitor PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_vcpmonitor PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_vcpmonitor PUBLIC MikroSDK.Log)
add_subdirectory(lib_vcpmonitor)
target_link_libraries(example_vcpmonitor PUBLIC Click.VCPmonitor)
############################ example_vcpmonitor GENERATED CODE END ###########################
