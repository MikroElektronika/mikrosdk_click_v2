cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_tmrangle LANGUAGES MikroC)
else()
    project(example_tmrangle LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_tmrangle
        example/main.c

)


############################ example_tmrangle GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_tmrangle PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_tmrangle PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_tmrangle PUBLIC MikroSDK.Log)
add_subdirectory(lib_tmrangle)
target_link_libraries(example_tmrangle PUBLIC Click.TMRAngle)
############################ example_tmrangle GENERATED CODE END ###########################
