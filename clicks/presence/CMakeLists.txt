cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_presence LANGUAGES MikroC)
else()
    project(example_presence LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_presence
        example/main.c

)


############################ example_presence GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_presence PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_presence PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_presence PUBLIC MikroSDK.Log)
add_subdirectory(lib_presence)
target_link_libraries(example_presence PUBLIC Click.Presence)
############################ example_presence GENERATED CODE END ###########################
