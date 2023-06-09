cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_lcdmono LANGUAGES MikroC)
else()
    project(example_lcdmono LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_lcdmono
        main.c

)


############################ example_lcdmono GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_lcdmono PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_lcdmono PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_lcdmono PUBLIC MikroSDK.Log)
add_subdirectory(lib_lcdmono)
target_link_libraries(example_lcdmono PUBLIC Click.LcdMono)
############################ example_lcdmono GENERATED CODE END ###########################
