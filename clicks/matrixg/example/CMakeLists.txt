cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_matrixg LANGUAGES MikroC)
else()
    project(example_matrixg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_matrixg
        main.c

)


############################ example_matrixg GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_matrixg PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_matrixg PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_matrixg PUBLIC MikroSDK.Log)
add_subdirectory(lib_matrixg)
target_link_libraries(example_matrixg PUBLIC Click.MatrixG)
############################ example_matrixg GENERATED CODE END ###########################
