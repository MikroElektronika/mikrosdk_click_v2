cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mbusmaster LANGUAGES MikroC)
else()
    project(example_mbusmaster LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mbusmaster
        example/main.c

)


############################ example_mbusmaster GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mbusmaster PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mbusmaster PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mbusmaster PUBLIC MikroSDK.Log)
add_subdirectory(lib_mbusmaster)
target_link_libraries(example_mbusmaster PUBLIC Click.MBusMaster)
############################ example_mbusmaster GENERATED CODE END ###########################
