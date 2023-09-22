cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_apc1sensor LANGUAGES MikroC)
else()
    project(example_apc1sensor LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_apc1sensor
        example/main.c
    
)


############################ example_apc1sensor GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_apc1sensor PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_apc1sensor PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_apc1sensor PUBLIC MikroSDK.Log)
add_subdirectory(lib_apc1sensor)
target_link_libraries(example_apc1sensor PUBLIC Click.APC1Sensor)
############################ example_apc1sensor GENERATED CODE END ###########################

