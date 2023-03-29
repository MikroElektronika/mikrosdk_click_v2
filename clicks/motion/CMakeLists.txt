cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_motion LANGUAGES MikroC)
else()
    project(example_motion LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_motion
        example/main.c

)


############################ example_motion GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_motion PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_motion PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_motion PUBLIC MikroSDK.Log)
add_subdirectory(lib_motion)
target_link_libraries(example_motion PUBLIC Click.Motion)
############################ example_motion GENERATED CODE END ###########################
