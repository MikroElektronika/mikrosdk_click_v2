cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_sqiflash LANGUAGES MikroC)
else()
    project(example_sqiflash LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_sqiflash
        main.c

)


############################ example_sqiflash GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_sqiflash PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_sqiflash PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_sqiflash PUBLIC MikroSDK.Log)
add_subdirectory(lib_sqiflash)
target_link_libraries(example_sqiflash PUBLIC Click.SqiFlash)
############################ example_sqiflash GENERATED CODE END ###########################
