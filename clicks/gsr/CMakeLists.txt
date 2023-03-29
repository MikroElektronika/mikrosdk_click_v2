cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gsr LANGUAGES MikroC)
else()
    project(example_gsr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gsr
        example/main.c

)


############################ example_gsr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gsr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gsr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gsr PUBLIC MikroSDK.Log)
add_subdirectory(lib_gsr)
target_link_libraries(example_gsr PUBLIC Click.Gsr)
############################ example_gsr GENERATED CODE END ###########################
