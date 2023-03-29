cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_airvelocity LANGUAGES MikroC)
else()
    project(example_airvelocity LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_airvelocity
        example/main.c

)


############################ example_airvelocity GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_airvelocity PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_airvelocity PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_airvelocity PUBLIC MikroSDK.Log)
add_subdirectory(lib_airvelocity)
target_link_libraries(example_airvelocity PUBLIC Click.AirVelocity)
############################ example_airvelocity GENERATED CODE END ###########################
