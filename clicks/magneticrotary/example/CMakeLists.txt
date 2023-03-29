cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_magneticrotary LANGUAGES MikroC)
else()
    project(example_magneticrotary LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_magneticrotary
        main.c

)


############################ example_magneticrotary GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_magneticrotary PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_magneticrotary PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_magneticrotary PUBLIC MikroSDK.Log)
add_subdirectory(lib_magneticrotary)
target_link_libraries(example_magneticrotary PUBLIC Click.MagneticRotary)
############################ example_magneticrotary GENERATED CODE END ###########################
