cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_ftdi LANGUAGES MikroC)
else()
    project(example_ftdi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_ftdi
        main.c
    
)


############################ example_ftdi GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_ftdi PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_ftdi PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_ftdi PUBLIC MikroSDK.Log)
add_subdirectory(lib_ftdi)
target_link_libraries(example_ftdi PUBLIC Click.FTDI)
############################ example_ftdi GENERATED CODE END ###########################

