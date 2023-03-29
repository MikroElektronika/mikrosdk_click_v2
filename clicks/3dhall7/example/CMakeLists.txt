cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c3dhall7 LANGUAGES MikroC)
else()
    project(example_c3dhall7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c3dhall7
        main.c

)


############################ example_c3dhall7 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c3dhall7 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c3dhall7 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c3dhall7 PUBLIC MikroSDK.Log)
add_subdirectory(lib_c3dhall7)
target_link_libraries(example_c3dhall7 PUBLIC Click.3dHall7)
############################ example_c3dhall7 GENERATED CODE END ###########################
