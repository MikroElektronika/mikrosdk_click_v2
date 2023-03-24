cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_vibrasense LANGUAGES MikroC)
else()
    project(example_vibrasense LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_vibrasense
        main.c

)


############################ example_vibrasense GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_vibrasense PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_vibrasense PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_vibrasense PUBLIC MikroSDK.Log)
add_subdirectory(lib_vibrasense)
target_link_libraries(example_vibrasense PUBLIC Click.VibraSense)
############################ example_vibrasense GENERATED CODE END ###########################
