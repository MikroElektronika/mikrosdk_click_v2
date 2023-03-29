cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_barometer LANGUAGES MikroC)
else()
    project(example_barometer LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_barometer
        main.c

)


############################ example_barometer GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_barometer PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_barometer PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_barometer PUBLIC MikroSDK.Log)
add_subdirectory(lib_barometer)
target_link_libraries(example_barometer PUBLIC Click.Barometer)
############################ example_barometer GENERATED CODE END ###########################
