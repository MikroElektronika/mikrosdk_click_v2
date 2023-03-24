cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c8x8y LANGUAGES MikroC)
else()
    project(example_c8x8y LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c8x8y
        example/main.c

)


############################ example_c8x8y GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c8x8y PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c8x8y PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c8x8y PUBLIC MikroSDK.Log)
add_subdirectory(lib_c8x8y)
target_link_libraries(example_c8x8y PUBLIC Click.8x8Y)
############################ example_c8x8y GENERATED CODE END ###########################
