cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_piezodriver LANGUAGES MikroC)
else()
    project(example_piezodriver LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_piezodriver
        main.c
    
)


############################ example_piezodriver GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_piezodriver PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_piezodriver PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_piezodriver PUBLIC MikroSDK.Log)
add_subdirectory(lib_piezodriver)
target_link_libraries(example_piezodriver PUBLIC Click.PiezoDriver)
############################ example_piezodriver GENERATED CODE END ###########################

