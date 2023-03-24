cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_sram LANGUAGES MikroC)
else()
    project(example_sram LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_sram
        main.c

)


############################ example_sram GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_sram PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_sram PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_sram PUBLIC MikroSDK.Log)
add_subdirectory(lib_sram)
target_link_libraries(example_sram PUBLIC Click.Sram)
############################ example_sram GENERATED CODE END ###########################
