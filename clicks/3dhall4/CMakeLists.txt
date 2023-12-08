cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c3dhall4 LANGUAGES MikroC)
else()
    project(example_c3dhall4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c3dhall4
        example/main.c
    
)


############################ example_c3dhall4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c3dhall4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c3dhall4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c3dhall4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_c3dhall4)
target_link_libraries(example_c3dhall4 PUBLIC Click.3DHall4)
############################ example_c3dhall4 GENERATED CODE END ###########################

