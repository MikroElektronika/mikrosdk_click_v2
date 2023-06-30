cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_magneto14 LANGUAGES MikroC)
else()
    project(example_magneto14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_magneto14
        example/main.c
    
)


############################ example_magneto14 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_magneto14 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_magneto14 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_magneto14 PUBLIC MikroSDK.Log)
add_subdirectory(lib_magneto14)
target_link_libraries(example_magneto14 PUBLIC Click.Magneto14)
############################ example_magneto14 GENERATED CODE END ###########################

