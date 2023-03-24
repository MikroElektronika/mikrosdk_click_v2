cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mic LANGUAGES MikroC)
else()
    project(example_mic LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mic
        example/main.c

)


############################ example_mic GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mic PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mic PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mic PUBLIC MikroSDK.Log)
add_subdirectory(lib_mic)
target_link_libraries(example_mic PUBLIC Click.Mic)
############################ example_mic GENERATED CODE END ###########################
