cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_usbcpower LANGUAGES MikroC)
else()
    project(example_usbcpower LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_usbcpower
        main.c
    
)


############################ example_usbcpower GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_usbcpower PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_usbcpower PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_usbcpower PUBLIC MikroSDK.Log)
add_subdirectory(lib_usbcpower)
target_link_libraries(example_usbcpower PUBLIC Click.USBCPower)
############################ example_usbcpower GENERATED CODE END ###########################

