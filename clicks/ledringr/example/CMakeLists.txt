cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ledringr LANGUAGES MikroC)
else()
    project(example_ledringr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ledringr
        main.c

)


############################ example_ledringr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ledringr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ledringr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ledringr PUBLIC MikroSDK.Log)
add_subdirectory(lib_ledringr)
target_link_libraries(example_ledringr PUBLIC Click.LedringR)
############################ example_ledringr GENERATED CODE END ###########################
