cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_matrixr LANGUAGES MikroC)
else()
    project(example_matrixr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_matrixr
        main.c

)


############################ example_matrixr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_matrixr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_matrixr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_matrixr PUBLIC MikroSDK.Log)
add_subdirectory(lib_matrixr)
target_link_libraries(example_matrixr PUBLIC Click.MatrixR)
############################ example_matrixr GENERATED CODE END ###########################
