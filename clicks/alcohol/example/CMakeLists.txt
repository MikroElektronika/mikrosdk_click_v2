cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_alcohol LANGUAGES MikroC)
else()
    project(example_alcohol LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_alcohol
        main.c

)


############################ example_alcohol GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_alcohol PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_alcohol PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_alcohol PUBLIC MikroSDK.Log)
add_subdirectory(lib_alcohol)
target_link_libraries(example_alcohol PUBLIC Click.Alcohol)
############################ example_alcohol GENERATED CODE END ###########################
