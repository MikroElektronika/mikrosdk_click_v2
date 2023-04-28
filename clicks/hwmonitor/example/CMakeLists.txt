cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hwmonitor LANGUAGES MikroC)
else()
    project(example_hwmonitor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hwmonitor
        main.c
    
)


############################ example_hwmonitor GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hwmonitor PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hwmonitor PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hwmonitor PUBLIC MikroSDK.Log)
add_subdirectory(lib_hwmonitor)
target_link_libraries(example_hwmonitor PUBLIC Click.HWMonitor)
############################ example_hwmonitor GENERATED CODE END ###########################

