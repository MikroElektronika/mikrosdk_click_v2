cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c3dhall LANGUAGES MikroC)
else()
    project(example_c3dhall LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c3dhall
        main.c

)


############################ example_c3dhall GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c3dhall PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c3dhall PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c3dhall PUBLIC MikroSDK.Log)
add_subdirectory(lib_c3dhall)
target_link_libraries(example_c3dhall PUBLIC Click.3DHall)
############################ example_c3dhall GENERATED CODE END ###########################
