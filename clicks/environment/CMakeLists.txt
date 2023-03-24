cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_environment  LANGUAGES MikroC)
else()
    project(example_environment  LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_environment
        example/main.c

)


############################ example_environment GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_environment  PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_environment  PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_environment  PUBLIC MikroSDK.Log)
add_subdirectory(lib_environment )
target_link_libraries(example_environment  PUBLIC Click.Environment)
############################ example_environment GENERATED CODE END ###########################
