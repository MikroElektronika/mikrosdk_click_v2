cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rotaryy LANGUAGES MikroC)
else()
    project(example_rotaryy LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rotaryy
        example/main.c

)


############################ example_rotaryy GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rotaryy PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rotaryy PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rotaryy PUBLIC MikroSDK.Log)
add_subdirectory(lib_rotaryy)
target_link_libraries(example_rotaryy PUBLIC Click.RotaryY)
############################ example_rotaryy GENERATED CODE END ###########################
