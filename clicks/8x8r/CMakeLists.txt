cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c8x8r LANGUAGES MikroC)
else()
    project(example_c8x8r LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c8x8r
        example/main.c

)


############################ example_c8x8r GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c8x8r PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c8x8r PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c8x8r PUBLIC MikroSDK.Log)
add_subdirectory(lib_c8x8r)
target_link_libraries(example_c8x8r PUBLIC Click.8x8R)
############################ example_c8x8r GENERATED CODE END ###########################
