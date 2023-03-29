cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lpg LANGUAGES MikroC)
else()
    project(example_lpg LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lpg
        example/main.c

)


############################ example_lpg GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lpg PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lpg PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lpg PUBLIC MikroSDK.Log)
add_subdirectory(lib_lpg)
target_link_libraries(example_lpg PUBLIC Click.LPG)
############################ example_lpg GENERATED CODE END ###########################
