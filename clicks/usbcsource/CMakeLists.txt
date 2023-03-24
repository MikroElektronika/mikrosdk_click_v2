cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_usbcsource LANGUAGES MikroC)
else()
    project(example_usbcsource LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_usbcsource
        example/main.c

)


############################ example_usbcsource GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_usbcsource PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_usbcsource PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_usbcsource PUBLIC MikroSDK.Log)
add_subdirectory(lib_usbcsource)
target_link_libraries(example_usbcsource PUBLIC Click.USBCSource)
############################ example_usbcsource GENERATED CODE END ###########################
