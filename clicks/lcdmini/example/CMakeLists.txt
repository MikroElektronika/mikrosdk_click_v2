cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lcdmini LANGUAGES MikroC)
else()
    project(example_lcdmini LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lcdmini
        main.c

)


############################ example_lcdmini GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lcdmini PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lcdmini PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lcdmini PUBLIC MikroSDK.Log)
add_subdirectory(lib_lcdmini)
target_link_libraries(example_lcdmini PUBLIC Click.LCDmini)
############################ example_lcdmini GENERATED CODE END ###########################
