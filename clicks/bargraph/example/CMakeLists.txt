cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_bargraph LANGUAGES MikroC)
else()
    project(example_bargraph LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_bargraph
        main.c

)


############################ example_bargraph GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_bargraph PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_bargraph PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_bargraph PUBLIC MikroSDK.Log)
add_subdirectory(lib_bargraph)
target_link_libraries(example_bargraph PUBLIC Click.BarGraph)
############################ example_bargraph GENERATED CODE END ###########################
