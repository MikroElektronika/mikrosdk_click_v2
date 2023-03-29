cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_clockgen LANGUAGES MikroC)
else()
    project(example_clockgen LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_clockgen
        main.c

)


############################ example_clockgen GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_clockgen PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_clockgen PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_clockgen PUBLIC MikroSDK.Log)
add_subdirectory(lib_clockgen)
target_link_libraries(example_clockgen PUBLIC Click.ClockGen)
############################ example_clockgen GENERATED CODE END ###########################
