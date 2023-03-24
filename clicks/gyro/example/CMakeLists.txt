cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gyro LANGUAGES MikroC)
else()
    project(example_gyro LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gyro
        main.c

)


############################ example_gyro GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gyro PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gyro PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gyro PUBLIC MikroSDK.Log)
add_subdirectory(lib_gyro)
target_link_libraries(example_gyro PUBLIC Click.Gyro)
############################ example_gyro GENERATED CODE END ###########################
