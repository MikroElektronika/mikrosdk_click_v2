cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_audioamp LANGUAGES MikroC)
else()
    project(example_audioamp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_audioamp
        example/main.c

)


############################ example_audioamp GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_audioamp PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_audioamp PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_audioamp PUBLIC MikroSDK.Log)
add_subdirectory(lib_audioamp)
target_link_libraries(example_audioamp PUBLIC Click.AudioAmp)
############################ example_audioamp GENERATED CODE END ###########################
