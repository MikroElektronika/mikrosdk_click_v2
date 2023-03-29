cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_stereoamp LANGUAGES MikroC)
else()
    project(example_stereoamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_stereoamp
        example/main.c

)


############################ example_stereoamp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_stereoamp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_stereoamp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_stereoamp PUBLIC MikroSDK.Log)
add_subdirectory(lib_stereoamp)
target_link_libraries(example_stereoamp PUBLIC Click.StereoAmp)
############################ example_stereoamp GENERATED CODE END ###########################
