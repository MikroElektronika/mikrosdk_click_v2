cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_gmrangle LANGUAGES MikroC)
else()
    project(example_gmrangle LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_gmrangle
        example/main.c

)


############################ example_gmrangle GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_gmrangle PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_gmrangle PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_gmrangle PUBLIC MikroSDK.Log)
add_subdirectory(lib_gmrangle)
target_link_libraries(example_gmrangle PUBLIC Click.GmrAngle)
############################ example_gmrangle GENERATED CODE END ###########################
