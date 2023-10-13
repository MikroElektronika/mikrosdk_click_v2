cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_speedradar LANGUAGES MikroC)
else()
    project(example_speedradar LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_speedradar
        main.c
    
)


############################ example_speedradar GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_speedradar PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_speedradar PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_speedradar PUBLIC MikroSDK.Log)
add_subdirectory(lib_speedradar)
target_link_libraries(example_speedradar PUBLIC Click.SpeedRadar)
############################ example_speedradar GENERATED CODE END ###########################

