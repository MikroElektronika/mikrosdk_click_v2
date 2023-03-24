cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_stepper16 LANGUAGES MikroC)
else()
    project(example_stepper16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_stepper16
        main.c

)


############################ example_stepper16 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_stepper16 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_stepper16 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_stepper16 PUBLIC MikroSDK.Log)
add_subdirectory(lib_stepper16)
target_link_libraries(example_stepper16 PUBLIC Click.Stepper16)
############################ example_stepper16 GENERATED CODE END ###########################
