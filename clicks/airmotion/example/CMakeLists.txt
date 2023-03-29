cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_airmotion LANGUAGES MikroC)
else()
    project(example_airmotion LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_airmotion
        main.c
    
)


############################ example_airmotion GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_airmotion PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_airmotion PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_airmotion PUBLIC MikroSDK.Log)
add_subdirectory(lib_airmotion)
target_link_libraries(example_airmotion PUBLIC Click.AirMotion)
############################ example_airmotion GENERATED CODE END ###########################

