cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rotaryrgb LANGUAGES MikroC)
else()
    project(example_rotaryrgb LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rotaryrgb
        main.c
    
)


############################ example_rotaryrgb GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rotaryrgb PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rotaryrgb PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rotaryrgb PUBLIC MikroSDK.Log)
add_subdirectory(lib_rotaryrgb)
target_link_libraries(example_rotaryrgb PUBLIC Click.RotaryRGB)
############################ example_rotaryrgb GENERATED CODE END ###########################

