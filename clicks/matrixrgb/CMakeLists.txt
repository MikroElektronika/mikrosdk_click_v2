cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_matrixrgb LANGUAGES MikroC)
else()
    project(example_matrixrgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_matrixrgb
        example/main.c

)


############################ example_matrixrgb GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_matrixrgb PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_matrixrgb PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_matrixrgb PUBLIC MikroSDK.Log)
add_subdirectory(lib_matrixrgb)
target_link_libraries(example_matrixrgb PUBLIC Click.MatrixRgb)
############################ example_matrixrgb GENERATED CODE END ###########################
