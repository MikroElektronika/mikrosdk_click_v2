cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_irthermo5v LANGUAGES MikroC)
else()
    project(example_irthermo5v LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_irthermo5v
        example/main.c

)


############################ example_irthermo5v GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_irthermo5v PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_irthermo5v PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_irthermo5v PUBLIC MikroSDK.Log)
add_subdirectory(lib_irthermo5v)
target_link_libraries(example_irthermo5v PUBLIC Click.IrThermo5V)
############################ example_irthermo5v GENERATED CODE END ###########################
