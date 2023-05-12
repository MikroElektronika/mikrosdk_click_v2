cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_accel18 LANGUAGES MikroC)
else()
    project(example_accel18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_accel18
        example/main.c

)


############################ example_accel18 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_accel18 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_accel18 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_accel18 PUBLIC MikroSDK.Log)
add_subdirectory(lib_accel18)
target_link_libraries(example_accel18 PUBLIC Click.Accel18)
############################ example_accel18 GENERATED CODE END ###########################
