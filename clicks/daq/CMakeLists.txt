cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_daq LANGUAGES MikroC)
else()
    project(example_daq LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_daq
        example/main.c

)


############################ example_daq GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_daq PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_daq PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_daq PUBLIC MikroSDK.Log)
add_subdirectory(lib_daq)
target_link_libraries(example_daq PUBLIC Click.DAQ)
############################ example_daq GENERATED CODE END ###########################
