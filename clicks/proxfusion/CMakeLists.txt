cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_proxfusion LANGUAGES MikroC)
else()
    project(example_proxfusion LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_proxfusion
        example/main.c

)


############################ example_proxfusion GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_proxfusion PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_proxfusion PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_proxfusion PUBLIC MikroSDK.Log)
add_subdirectory(lib_proxfusion)
target_link_libraries(example_proxfusion PUBLIC Click.ProxFusion)
############################ example_proxfusion GENERATED CODE END ###########################
