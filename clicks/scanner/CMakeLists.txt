cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_scanner LANGUAGES MikroC)
else()
    project(example_scanner LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_scanner
        example/main.c

)


############################ example_scanner GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_scanner PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_scanner PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_scanner PUBLIC MikroSDK.Log)
add_subdirectory(lib_scanner)
target_link_libraries(example_scanner PUBLIC Click.Scanner)
############################ example_scanner GENERATED CODE END ###########################
