cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_wirelesssun LANGUAGES MikroC)
else()
    project(example_wirelesssun LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_wirelesssun
        main.c

)


############################ example_wirelesssun GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_wirelesssun PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_wirelesssun PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_wirelesssun PUBLIC MikroSDK.Log)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(example_wirelesssun PUBLIC MikroSDK.Conversions)
add_subdirectory(lib_wirelesssun)
target_link_libraries(example_wirelesssun PUBLIC Click.WirelessSUN)
############################ example_wirelesssun GENERATED CODE END ###########################
