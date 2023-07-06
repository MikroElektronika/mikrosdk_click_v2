cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_usbmux LANGUAGES MikroC)
else()
    project(example_usbmux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_usbmux
        main.c
    
)


############################ example_usbmux GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_usbmux PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_usbmux PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_usbmux PUBLIC MikroSDK.Log)
add_subdirectory(lib_usbmux)
target_link_libraries(example_usbmux PUBLIC Click.USBMUX)
############################ example_usbmux GENERATED CODE END ###########################

