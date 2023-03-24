cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_fan LANGUAGES MikroC)
else()
    project(example_fan LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_fan
        main.c

)


############################ example_fan GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_fan PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_fan PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_fan PUBLIC MikroSDK.Log)
add_subdirectory(lib_fan)
target_link_libraries(example_fan PUBLIC Click.Fan)
############################ example_fan GENERATED CODE END ###########################
