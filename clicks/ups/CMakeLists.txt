cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ups LANGUAGES MikroC)
else()
    project(example_ups LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ups
        example/main.c

)


############################ example_ups GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ups PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ups PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ups PUBLIC MikroSDK.Log)
add_subdirectory(lib_ups)
target_link_libraries(example_ups PUBLIC Click.Ups)
############################ example_ups GENERATED CODE END ###########################
