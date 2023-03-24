cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pixi LANGUAGES MikroC)
else()
    project(example_pixi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pixi
        example/main.c

)


############################ example_pixi GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pixi PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pixi PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pixi PUBLIC MikroSDK.Log)
add_subdirectory(lib_pixi)
target_link_libraries(example_pixi PUBLIC Click.Pixi)
############################ example_pixi GENERATED CODE END ###########################
