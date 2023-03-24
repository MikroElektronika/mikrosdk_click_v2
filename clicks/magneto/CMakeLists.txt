cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_magneto LANGUAGES MikroC)
else()
    project(example_magneto LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_magneto
        example/main.c

)


############################ example_magneto GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_magneto PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_magneto PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_magneto PUBLIC MikroSDK.Log)
add_subdirectory(lib_magneto)
target_link_libraries(example_magneto PUBLIC Click.Magneto)
############################ example_magneto GENERATED CODE END ###########################
