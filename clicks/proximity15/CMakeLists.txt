cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_proximity15 LANGUAGES MikroC)
else()
    project(example_proximity15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_proximity15
        example/main.c

)


############################ example_proximity15 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_proximity15 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_proximity15 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_proximity15 PUBLIC MikroSDK.Log)
add_subdirectory(lib_proximity15)
target_link_libraries(example_proximity15 PUBLIC Click.Proximity15)
############################ example_proximity15 GENERATED CODE END ###########################
