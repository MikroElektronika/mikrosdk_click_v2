cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rn4870 LANGUAGES MikroC)
else()
    project(example_rn4870 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rn4870
        example/main.c

)


############################ example_rn4870 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rn4870 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rn4870 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rn4870 PUBLIC MikroSDK.Log)
add_subdirectory(lib_rn4870)
target_link_libraries(example_rn4870 PUBLIC Click.Rn4870)
############################ example_rn4870 GENERATED CODE END ###########################
