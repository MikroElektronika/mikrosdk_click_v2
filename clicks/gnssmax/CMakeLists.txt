cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gnssmax LANGUAGES MikroC)
else()
    project(example_gnssmax LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gnssmax
        example/main.c

)


############################ example_gnssmax GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gnssmax PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gnssmax PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gnssmax PUBLIC MikroSDK.Log)
add_subdirectory(lib_gnssmax)
target_link_libraries(example_gnssmax PUBLIC Click.GNSSMAX)
############################ example_gnssmax GENERATED CODE END ###########################
