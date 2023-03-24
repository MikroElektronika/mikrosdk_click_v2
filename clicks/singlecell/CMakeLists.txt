cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_singlecell LANGUAGES MikroC)
else()
    project(example_singlecell LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_singlecell
        example/main.c

)


############################ example_singlecell GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_singlecell PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_singlecell PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_singlecell PUBLIC MikroSDK.Log)
add_subdirectory(lib_singlecell)
target_link_libraries(example_singlecell PUBLIC Click.SingleCell)
############################ example_singlecell GENERATED CODE END ###########################
