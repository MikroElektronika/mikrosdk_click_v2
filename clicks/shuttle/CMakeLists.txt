cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_shuttle LANGUAGES MikroC)
else()
    project(example_shuttle LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_shuttle
        example/main.c

)


############################ example_shuttle GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_shuttle PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_shuttle PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_shuttle PUBLIC MikroSDK.Log)
add_subdirectory(lib_shuttle)
target_link_libraries(example_shuttle PUBLIC Click.Shuttle)
############################ example_shuttle GENERATED CODE END ###########################
