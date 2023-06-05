cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_servo LANGUAGES MikroC)
else()
    project(example_servo LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_servo
        example/main.c

)


############################ example_servo GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_servo PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_servo PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_servo PUBLIC MikroSDK.Log)
add_subdirectory(lib_servo)
target_link_libraries(example_servo PUBLIC Click.Servo)
############################ example_servo GENERATED CODE END ###########################
