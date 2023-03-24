cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hbridgedriver LANGUAGES MikroC)
else()
    project(example_hbridgedriver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hbridgedriver
        main.c

)


############################ example_hbridgedriver GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hbridgedriver PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hbridgedriver PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hbridgedriver PUBLIC MikroSDK.Log)
add_subdirectory(lib_hbridgedriver)
target_link_libraries(example_hbridgedriver PUBLIC Click.HBridgeDriver)
############################ example_hbridgedriver GENERATED CODE END ###########################
