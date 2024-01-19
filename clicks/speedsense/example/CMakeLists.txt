cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_speedsense LANGUAGES MikroC)
else()
    project(example_speedsense LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_speedsense
        main.c
    
)


############################ example_speedsense GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_speedsense PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_speedsense PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_speedsense PUBLIC MikroSDK.Log)
add_subdirectory(lib_speedsense)
target_link_libraries(example_speedsense PUBLIC Click.SpeedSense)
############################ example_speedsense GENERATED CODE END ###########################

