cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_batterysource LANGUAGES MikroC)
else()
    project(example_batterysource LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_batterysource
        main.c
    
)


############################ example_batterysource GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_batterysource PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_batterysource PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_batterysource PUBLIC MikroSDK.Log)
add_subdirectory(lib_batterysource)
target_link_libraries(example_batterysource PUBLIC Click.BatterySource)
############################ example_batterysource GENERATED CODE END ###########################

