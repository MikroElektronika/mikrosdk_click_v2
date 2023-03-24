cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pressure LANGUAGES MikroC)
else()
    project(example_pressure LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pressure
        main.c

)


############################ example_pressure GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pressure PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pressure PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pressure PUBLIC MikroSDK.Log)
add_subdirectory(lib_pressure)
target_link_libraries(example_pressure PUBLIC Click.Pressure)
############################ example_pressure GENERATED CODE END ###########################
