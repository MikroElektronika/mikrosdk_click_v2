cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_analogmux LANGUAGES MikroC)
else()
    project(example_analogmux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_analogmux
        main.c

)


############################ example_analogmux GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_analogmux PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_analogmux PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_analogmux PUBLIC MikroSDK.Log)
add_subdirectory(lib_analogmux)
target_link_libraries(example_analogmux PUBLIC Click.AnalogMUX)
############################ example_analogmux GENERATED CODE END ###########################
