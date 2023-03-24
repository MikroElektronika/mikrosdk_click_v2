cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_rotaryo LANGUAGES MikroC)
else()
    project(example_rotaryo LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_rotaryo
        main.c

)


############################ example_rotaryo GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_rotaryo PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_rotaryo PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_rotaryo PUBLIC MikroSDK.Log)
add_subdirectory(lib_rotaryo)
target_link_libraries(example_rotaryo PUBLIC Click.RotaryO)
############################ example_rotaryo GENERATED CODE END ###########################
