cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_noise LANGUAGES MikroC)
else()
    project(example_noise LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_noise
        example/main.c

)


############################ example_noise GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_noise PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_noise PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_noise PUBLIC MikroSDK.Log)
add_subdirectory(lib_noise)
target_link_libraries(example_noise PUBLIC Click.Noise)
############################ example_noise GENERATED CODE END ###########################
