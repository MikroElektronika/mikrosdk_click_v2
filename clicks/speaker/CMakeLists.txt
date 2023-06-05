cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_speaker LANGUAGES MikroC)
else()
    project(example_speaker LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_speaker
        example/main.c

)


############################ example_speaker GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_speaker PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_speaker PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_speaker PUBLIC MikroSDK.Log)
add_subdirectory(lib_speaker)
target_link_libraries(example_speaker PUBLIC Click.Speaker)
############################ example_speaker GENERATED CODE END ###########################
