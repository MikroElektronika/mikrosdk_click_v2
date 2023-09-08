cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_stepdown8 LANGUAGES MikroC)
else()
    project(example_stepdown8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_stepdown8
        example/main.c
    
)


############################ example_stepdown8 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_stepdown8 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_stepdown8 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_stepdown8 PUBLIC MikroSDK.Log)
add_subdirectory(lib_stepdown8)
target_link_libraries(example_stepdown8 PUBLIC Click.StepDown8)
############################ example_stepdown8 GENERATED CODE END ###########################

