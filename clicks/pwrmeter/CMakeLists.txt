cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pwrmeter LANGUAGES MikroC)
else()
    project(example_pwrmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pwrmeter
        example/main.c

)


############################ example_pwrmeter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pwrmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pwrmeter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pwrmeter PUBLIC MikroSDK.Log)
add_subdirectory(lib_pwrmeter)
target_link_libraries(example_pwrmeter PUBLIC Click.PwrMeter)
############################ example_pwrmeter GENERATED CODE END ###########################
