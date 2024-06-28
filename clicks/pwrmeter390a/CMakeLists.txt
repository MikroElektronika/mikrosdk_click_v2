cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pwrmeter390a LANGUAGES MikroC)
else()
    project(example_pwrmeter390a LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pwrmeter390a
        example/main.c

)


############################ example_pwrmeter390a GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pwrmeter390a PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pwrmeter390a PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pwrmeter390a PUBLIC MikroSDK.Log)
add_subdirectory(lib_pwrmeter390a)
target_link_libraries(example_pwrmeter390a PUBLIC Click.PWRMeter390A)
############################ example_pwrmeter390a GENERATED CODE END ###########################
