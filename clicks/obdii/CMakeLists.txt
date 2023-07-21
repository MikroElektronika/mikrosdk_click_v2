cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_obdii LANGUAGES MikroC)
else()
    project(example_obdii LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_obdii
        example/main.c
    
)


############################ example_obdii GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_obdii PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_obdii PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_obdii PUBLIC MikroSDK.Log)
add_subdirectory(lib_obdii)
target_link_libraries(example_obdii PUBLIC Click.OBDII)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_obdii PUBLIC MikroSDK.Conversions)
############################ example_obdii GENERATED CODE END ###########################

