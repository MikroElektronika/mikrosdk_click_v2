cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c3dhall9 LANGUAGES MikroC)
else()
    project(example_c3dhall9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c3dhall9
        example/main.c

)


############################ example_c3dhall9 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c3dhall9 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c3dhall9 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c3dhall9 PUBLIC MikroSDK.Log)
add_subdirectory(lib_c3dhall9)
target_link_libraries(example_c3dhall9 PUBLIC Click.3DHall9)
############################ example_c3dhall9 GENERATED CODE END ###########################
