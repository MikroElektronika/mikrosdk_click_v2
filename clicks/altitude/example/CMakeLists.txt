cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_altitude LANGUAGES MikroC)
else()
    project(example_altitude LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_altitude
        main.c

)


############################ example_altitude GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_altitude PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_altitude PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_altitude PUBLIC MikroSDK.Log)
add_subdirectory(lib_altitude)
target_link_libraries(example_altitude PUBLIC Click.Altitude)
############################ example_altitude GENERATED CODE END ###########################
