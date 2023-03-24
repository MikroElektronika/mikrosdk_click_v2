cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_accel25 LANGUAGES MikroC)
else()
    project(example_accel25 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_accel25
        main.c
    
)


############################ example_accel25 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_accel25 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_accel25 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_accel25 PUBLIC MikroSDK.Log)
add_subdirectory(lib_accel25)
target_link_libraries(example_accel25 PUBLIC Click.Accel25)
############################ example_accel25 GENERATED CODE END ###########################

