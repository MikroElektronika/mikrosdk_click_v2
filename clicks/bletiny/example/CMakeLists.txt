cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_bletiny LANGUAGES MikroC)
else()
    project(example_bletiny LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_bletiny
        main.c

)


############################ example_bletiny GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_bletiny PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_bletiny PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_bletiny PUBLIC MikroSDK.Log)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_bletiny PUBLIC MikroSDK.Conversions)
add_subdirectory(lib_bletiny)
target_link_libraries(example_bletiny PUBLIC Click.BLETINY)
############################ example_bletiny GENERATED CODE END ###########################
