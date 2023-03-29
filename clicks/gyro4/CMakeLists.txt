cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gyro4 LANGUAGES MikroC)
else()
    project(example_gyro4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gyro4
        example/main.c

)


############################ example_gyro4 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gyro4 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gyro4 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gyro4 PUBLIC MikroSDK.Log)
add_subdirectory(lib_gyro4)
target_link_libraries(example_gyro4 PUBLIC Click.Gyro4)
############################ example_gyro4 GENERATED CODE END ###########################
