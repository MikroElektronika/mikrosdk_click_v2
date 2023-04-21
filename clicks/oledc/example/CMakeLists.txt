cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_oledc LANGUAGES MikroC)
else()
    project(example_oledc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_oledc
        main.c
)


############################ example_oledc GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_oledc PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_oledc PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_oledc PUBLIC MikroSDK.Log)
add_subdirectory(lib_oledc)
target_link_libraries(example_oledc PUBLIC Click.OledC)
############################ example_oledc GENERATED CODE END ###########################
