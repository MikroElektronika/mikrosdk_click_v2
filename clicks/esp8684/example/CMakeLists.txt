cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_esp8684 LANGUAGES MikroC)
else()
    project(example_esp8684 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_esp8684
        main.c
    
)


############################ example_esp8684 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_esp8684 PUBLIC MikroC.Core)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_esp8684 PUBLIC MikroSDK.Conversions)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_esp8684 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_esp8684 PUBLIC MikroSDK.Log)
add_subdirectory(lib_esp8684)
target_link_libraries(example_esp8684 PUBLIC Click.ESP8684)
############################ example_esp8684 GENERATED CODE END ###########################

