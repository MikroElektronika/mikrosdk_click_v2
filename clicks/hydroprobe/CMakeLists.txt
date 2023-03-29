cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_hydroprobe LANGUAGES MikroC)
else()
    project(example_hydroprobe LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_hydroprobe
        example/main.c

)


############################ example_hydroprobe GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_hydroprobe PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_hydroprobe PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_hydroprobe PUBLIC MikroSDK.Log)
add_subdirectory(lib_hydroprobe)
target_link_libraries(example_hydroprobe PUBLIC Click.HydroProbe)
############################ example_hydroprobe GENERATED CODE END ###########################
