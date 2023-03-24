cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gyro5 LANGUAGES MikroC)
else()
    project(example_gyro5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gyro5
        example/main.c

)


############################ example_gyro5 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gyro5 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gyro5 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gyro5 PUBLIC MikroSDK.Log)
add_subdirectory(lib_gyro5)
target_link_libraries(example_gyro5 PUBLIC Click.Gyro5)
############################ example_gyro5 GENERATED CODE END ###########################
