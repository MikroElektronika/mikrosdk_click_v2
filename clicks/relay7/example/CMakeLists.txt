cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_relay7 LANGUAGES MikroC)
else()
    project(example_relay7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_relay7
        main.c
    
)


############################ example_relay7 GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_relay7 PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_relay7 PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_relay7 PUBLIC MikroSDK.Log)
add_subdirectory(lib_relay7)
target_link_libraries(example_relay7 PUBLIC Click.Relay7)
############################ example_relay7 GENERATED CODE END ###########################

