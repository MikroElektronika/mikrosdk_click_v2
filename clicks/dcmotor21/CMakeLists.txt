cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_dcmotor21 LANGUAGES MikroC)
else()
    project(example_dcmotor21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_dcmotor21
        example/main.c

)


############################ example_dcmotor21 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_dcmotor21 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_dcmotor21 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_dcmotor21 PUBLIC MikroSDK.Log)
add_subdirectory(lib_dcmotor21)
target_link_libraries(example_dcmotor21 PUBLIC Click.DCMotor21)
############################ example_dcmotor21 GENERATED CODE END ###########################
