cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_stspin220 LANGUAGES MikroC)
else()
    project(example_stspin220 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_stspin220
        main.c
    
)


############################ example_stspin220 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_stspin220 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_stspin220 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_stspin220 PUBLIC MikroSDK.Log)
add_subdirectory(lib_stspin220)
target_link_libraries(example_stspin220 PUBLIC Click.STSPIN220)
############################ example_stspin220 GENERATED CODE END ###########################

