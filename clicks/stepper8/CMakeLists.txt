cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_stepper8 LANGUAGES MikroC)
else()
    project(example_stepper8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_stepper8
        example/main.c
    
)


############################ example_stepper8 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_stepper8 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_stepper8 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_stepper8 PUBLIC MikroSDK.Log)
add_subdirectory(lib_stepper8)
target_link_libraries(example_stepper8 PUBLIC Click.Stepper8)
############################ example_stepper8 GENERATED CODE END ###########################

