cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_waterdetect LANGUAGES MikroC)
else()
    project(example_waterdetect LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_waterdetect
        example/main.c

)


############################ example_waterdetect GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_waterdetect PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_waterdetect PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_waterdetect PUBLIC MikroSDK.Log)
add_subdirectory(lib_waterdetect)
target_link_libraries(example_waterdetect PUBLIC Click.WaterDetect)
############################ example_waterdetect GENERATED CODE END ###########################
