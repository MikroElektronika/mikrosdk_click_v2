cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_i2ctospi LANGUAGES MikroC)
else()
    project(example_i2ctospi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_i2ctospi
        example/main.c

)


############################ example_i2ctospi GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_i2ctospi PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_i2ctospi PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_i2ctospi PUBLIC MikroSDK.Log)
add_subdirectory(lib_i2ctospi)
target_link_libraries(example_i2ctospi PUBLIC Click.I2cToSpi)
############################ example_i2ctospi GENERATED CODE END ###########################
