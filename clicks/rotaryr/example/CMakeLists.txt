cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rotaryr LANGUAGES MikroC)
else()
    project(example_rotaryr LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rotaryr
        main.c

)


############################ example_rotaryr GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rotaryr PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rotaryr PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rotaryr PUBLIC MikroSDK.Log)
add_subdirectory(lib_rotaryr)
target_link_libraries(example_rotaryr PUBLIC Click.RotaryR)
############################ example_rotaryr GENERATED CODE END ###########################
