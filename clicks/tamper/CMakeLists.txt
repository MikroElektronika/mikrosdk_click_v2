cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_tamper LANGUAGES MikroC)
else()
    project(example_tamper LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_tamper
        example/main.c

)


############################ example_tamper GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_tamper PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_tamper PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_tamper PUBLIC MikroSDK.Log)
add_subdirectory(lib_tamper)
target_link_libraries(example_tamper PUBLIC Click.Tamper)
############################ example_tamper GENERATED CODE END ###########################
