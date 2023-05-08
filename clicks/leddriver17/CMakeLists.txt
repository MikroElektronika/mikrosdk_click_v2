cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_leddriver17 LANGUAGES MikroC)
else()
    project(example_leddriver17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_leddriver17
        example/main.c
    
)


############################ example_leddriver17 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_leddriver17 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_leddriver17 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_leddriver17 PUBLIC MikroSDK.Log)
add_subdirectory(lib_leddriver17)
target_link_libraries(example_leddriver17 PUBLIC Click.LEDDriver17)
############################ example_leddriver17 GENERATED CODE END ###########################

