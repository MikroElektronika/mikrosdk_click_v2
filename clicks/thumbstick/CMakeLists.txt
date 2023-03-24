cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_thumbstick LANGUAGES MikroC)
else()
    project(example_thumbstick LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_thumbstick
        example/main.c

)


############################ example_thumbstick GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_thumbstick PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_thumbstick PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_thumbstick PUBLIC MikroSDK.Log)
add_subdirectory(lib_thumbstick)
target_link_libraries(example_thumbstick PUBLIC Click.Thumbstick)
############################ example_thumbstick GENERATED CODE END ###########################
