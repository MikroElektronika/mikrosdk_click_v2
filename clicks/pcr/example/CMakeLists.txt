cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pcr LANGUAGES MikroC)
else()
    project(example_pcr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pcr
        main.c
    
)


############################ example_pcr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pcr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pcr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pcr PUBLIC MikroSDK.Log)
add_subdirectory(lib_pcr)
target_link_libraries(example_pcr PUBLIC Click.PCR)
############################ example_pcr GENERATED CODE END ###########################

