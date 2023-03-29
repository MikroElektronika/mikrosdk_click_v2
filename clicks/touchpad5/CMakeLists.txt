cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_touchpad5 LANGUAGES MikroC)
else()
    project(example_touchpad5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_touchpad5
        example/main.c

)


############################ example_touchpad5 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_touchpad5 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_touchpad5 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_touchpad5 PUBLIC MikroSDK.Log)
add_subdirectory(lib_touchpad5)
target_link_libraries(example_touchpad5 PUBLIC Click.TouchPad5)
############################ example_touchpad5 GENERATED CODE END ###########################
