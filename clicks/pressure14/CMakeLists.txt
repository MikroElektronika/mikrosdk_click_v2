cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pressure14 LANGUAGES MikroC)
else()
    project(example_pressure14 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pressure14
        example/main.c

)


############################ example_pressure14 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pressure14 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pressure14 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pressure14 PUBLIC MikroSDK.Log)
add_subdirectory(lib_pressure14)
target_link_libraries(example_pressure14 PUBLIC Click.Pressure14)
############################ example_pressure14 GENERATED CODE END ###########################
