cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_shutter LANGUAGES MikroC)
else()
    project(example_shutter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_shutter
        example/main.c

)


############################ example_shutter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_shutter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_shutter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_shutter PUBLIC MikroSDK.Log)
add_subdirectory(lib_shutter)
target_link_libraries(example_shutter PUBLIC Click.Shutter)
############################ example_shutter GENERATED CODE END ###########################
