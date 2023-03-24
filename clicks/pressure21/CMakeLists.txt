cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_pressure21 LANGUAGES MikroC)
else()
    project(example_pressure21 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_pressure21
        example/main.c

)


############################ example_pressure21 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_pressure21 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_pressure21 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_pressure21 PUBLIC MikroSDK.Log)
add_subdirectory(lib_pressure21)
target_link_libraries(example_pressure21 PUBLIC Click.Pressure21)
############################ example_pressure21 GENERATED CODE END ###########################
