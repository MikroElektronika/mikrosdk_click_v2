cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_tempprobe LANGUAGES MikroC)
else()
    project(example_tempprobe LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_tempprobe
        main.c

)


############################ example_tempprobe GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_tempprobe PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_tempprobe PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_tempprobe PUBLIC MikroSDK.Log)
add_subdirectory(lib_tempprobe)
target_link_libraries(example_tempprobe PUBLIC Click.TempProbe)
############################ example_tempprobe GENERATED CODE END ###########################
