cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_i2cextend LANGUAGES MikroC)
else()
    project(example_i2cextend LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_i2cextend
        main.c

)


############################ example_i2cextend GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_i2cextend PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_i2cextend PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_i2cextend PUBLIC MikroSDK.Log)
add_subdirectory(lib_i2cextend)
target_link_libraries(example_i2cextend PUBLIC Click.I2CExtend)
############################ example_i2cextend GENERATED CODE END ###########################
