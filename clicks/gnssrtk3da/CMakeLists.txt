cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gnssrtk3da LANGUAGES MikroC)
else()
    project(example_gnssrtk3da LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gnssrtk3da
        example/main.c
    
)


############################ example_gnssrtk3da GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gnssrtk3da PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gnssrtk3da PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gnssrtk3da PUBLIC MikroSDK.Log)
add_subdirectory(lib_gnssrtk3da)
target_link_libraries(example_gnssrtk3da PUBLIC Click.GNSSRTK3DA)
############################ example_gnssrtk3da GENERATED CODE END ###########################

