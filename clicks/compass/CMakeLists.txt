cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_compass LANGUAGES MikroC)
else()
    project(example_compass LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_compass
        example/main.c

)


############################ example_compass GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_compass PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_compass PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_compass PUBLIC MikroSDK.Log)
add_subdirectory(lib_compass)
target_link_libraries(example_compass PUBLIC Click.Compass)
############################ example_compass GENERATED CODE END ###########################
