cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_nanobeacon LANGUAGES MikroC)
else()
    project(example_nanobeacon LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_nanobeacon
        example/main.c
    
)


############################ example_nanobeacon GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_nanobeacon PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_nanobeacon PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_nanobeacon PUBLIC MikroSDK.Log)
add_subdirectory(lib_nanobeacon)
target_link_libraries(example_nanobeacon PUBLIC Click.NanoBeacon)
############################ example_nanobeacon GENERATED CODE END ###########################

