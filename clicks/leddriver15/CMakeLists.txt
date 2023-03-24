cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_leddriver15 LANGUAGES MikroC)
else()
    project(example_leddriver15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_leddriver15
        example/main.c
    
)


############################ example_leddriver15 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_leddriver15 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_leddriver15 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_leddriver15 PUBLIC MikroSDK.Log)
add_subdirectory(lib_leddriver15)
target_link_libraries(example_leddriver15 PUBLIC Click.LEDDriver15)
############################ example_leddriver15 GENERATED CODE END ###########################

