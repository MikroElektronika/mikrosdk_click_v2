cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_nvsram LANGUAGES MikroC)
else()
    project(example_nvsram LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_nvsram
        main.c

)


############################ example_nvsram GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_nvsram PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_nvsram PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_nvsram PUBLIC MikroSDK.Log)
add_subdirectory(lib_nvsram)
target_link_libraries(example_nvsram PUBLIC Click.nvSRAM)
############################ example_nvsram GENERATED CODE END ###########################
