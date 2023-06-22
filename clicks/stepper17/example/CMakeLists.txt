cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_stepper17 LANGUAGES MikroC)
else()
    project(example_stepper17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_stepper17
        main.c

)


############################ example_stepper17 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_stepper17 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_stepper17 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_stepper17 PUBLIC MikroSDK.Log)
add_subdirectory(lib_stepper17)
target_link_libraries(example_stepper17 PUBLIC Click.Stepper17)
############################ example_stepper17 GENERATED CODE END ###########################
