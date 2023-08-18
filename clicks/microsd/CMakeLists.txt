cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_microsd LANGUAGES MikroC)
else()
    project(example_microsd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_microsd
        example/main.c
    
)


############################ example_microsd GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_microsd PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_microsd PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_microsd PUBLIC MikroSDK.Log)
add_subdirectory(lib_microsd)
target_link_libraries(example_microsd PUBLIC Click.microSD)
############################ example_microsd GENERATED CODE END ###########################

