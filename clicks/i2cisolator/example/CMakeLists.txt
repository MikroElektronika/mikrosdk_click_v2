cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_i2cisolator LANGUAGES MikroC)
else()
    project(example_i2cisolator LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_i2cisolator
        main.c

)


############################ example_i2cisolator GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_i2cisolator PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_i2cisolator PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_i2cisolator PUBLIC MikroSDK.Log)
add_subdirectory(lib_i2cisolator)
target_link_libraries(example_i2cisolator PUBLIC Click.I2Cisolator)
############################ example_i2cisolator GENERATED CODE END ###########################
