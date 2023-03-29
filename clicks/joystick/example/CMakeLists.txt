cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_joystick LANGUAGES MikroC)
else()
    project(example_joystick LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_joystick
        main.c

)


############################ example_joystick GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_joystick PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_joystick PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_joystick PUBLIC MikroSDK.Log)
add_subdirectory(lib_joystick)
target_link_libraries(example_joystick PUBLIC Click.Joystick)
############################ example_joystick GENERATED CODE END ###########################
