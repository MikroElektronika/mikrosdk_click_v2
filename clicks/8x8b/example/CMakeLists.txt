cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c8x8b LANGUAGES MikroC)
else()
    project(example_c8x8b LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c8x8b
        main.c

)


############################ example_c8x8b GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c8x8b PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c8x8b PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c8x8b PUBLIC MikroSDK.Log)
add_subdirectory(lib_c8x8b)
target_link_libraries(example_c8x8b PUBLIC Click.8X8B)
############################ example_c8x8b GENERATED CODE END ###########################
