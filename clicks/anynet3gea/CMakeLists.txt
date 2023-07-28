cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_anynet3gea LANGUAGES MikroC)
else()
    project(example_anynet3gea LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_anynet3gea
        example/main.c

)


############################ example_anynet3gea GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_anynet3gea PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_anynet3gea PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_anynet3gea PUBLIC MikroSDK.Log)
add_subdirectory(lib_anynet3gea)
target_link_libraries(example_anynet3gea PUBLIC Click.AnyNet3GEA)
############################ example_anynet3gea GENERATED CODE END ###########################
