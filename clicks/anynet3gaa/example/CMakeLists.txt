cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_anynet3gaa LANGUAGES MikroC)
else()
    project(example_anynet3gaa LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_anynet3gaa
        main.c

)


############################ example_anynet3gaa GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_anynet3gaa PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_anynet3gaa PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_anynet3gaa PUBLIC MikroSDK.Log)
add_subdirectory(lib_anynet3gaa)
target_link_libraries(example_anynet3gaa PUBLIC Click.AnyNet3GAA)
############################ example_anynet3gaa GENERATED CODE END ###########################
