cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_mpuimu LANGUAGES MikroC)
else()
    project(example_mpuimu LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_mpuimu
        example/main.c

)


############################ example_mpuimu GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_mpuimu PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_mpuimu PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_mpuimu PUBLIC MikroSDK.Log)
add_subdirectory(lib_mpuimu)
target_link_libraries(example_mpuimu PUBLIC Click.MpuImu)
############################ example_mpuimu GENERATED CODE END ###########################
