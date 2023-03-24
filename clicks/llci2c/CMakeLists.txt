cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_llci2c LANGUAGES MikroC)
else()
    project(example_llci2c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_llci2c
        example/main.c

)


############################ example_llci2c GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_llci2c PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_llci2c PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_llci2c PUBLIC MikroSDK.Log)
add_subdirectory(lib_llci2c)
target_link_libraries(example_llci2c PUBLIC Click.LlcI2c)
############################ example_llci2c GENERATED CODE END ###########################
