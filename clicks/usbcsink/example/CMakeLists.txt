cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(example_usbcsink LANGUAGES MikroC)
else()
    project(example_usbcsink LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_executable(example_usbcsink
        main.c

)


############################ example_usbcsink GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(example_usbcsink PUBLIC MikroC.Core)
find_package(MikroSDK.Board REQUIRED)
target_link_libraries(example_usbcsink PUBLIC MikroSDK.Board)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(example_usbcsink PUBLIC MikroSDK.Log)
add_subdirectory(lib_usbcsink)
target_link_libraries(example_usbcsink PUBLIC Click.USBCSink)
############################ example_usbcsink GENERATED CODE END ###########################
