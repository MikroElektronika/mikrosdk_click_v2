cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gaussmeter LANGUAGES MikroC)
else()
    project(example_gaussmeter LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gaussmeter
        main.c

)


############################ example_gaussmeter GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gaussmeter PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gaussmeter PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gaussmeter PUBLIC MikroSDK.Log)
add_subdirectory(lib_gaussmeter)
target_link_libraries(example_gaussmeter PUBLIC Click.Gaussmeter)
############################ example_gaussmeter GENERATED CODE END ###########################
