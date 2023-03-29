cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_c8800retro LANGUAGES MikroC)
else()
    project(example_c8800retro LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_c8800retro
        example/main.c

)


############################ example_c8800retro GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_c8800retro PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_c8800retro PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_c8800retro PUBLIC MikroSDK.Log)
add_subdirectory(lib_c8800retro)
target_link_libraries(example_c8800retro PUBLIC Click.8800Retro)
############################ example_c8800retro GENERATED CODE END ###########################
