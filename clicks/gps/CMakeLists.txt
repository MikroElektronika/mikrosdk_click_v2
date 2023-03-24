cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gps LANGUAGES MikroC)
else()
    project(example_gps LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gps
        example/main.c

)


############################ example_gps GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gps PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gps PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gps PUBLIC MikroSDK.Log)
add_subdirectory(lib_gps)
target_link_libraries(example_gps PUBLIC Click.Gps)
############################ example_gps GENERATED CODE END ###########################
