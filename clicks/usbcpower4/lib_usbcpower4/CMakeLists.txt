cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbcpower4 LANGUAGES MikroC)
else()
    project(lib_usbcpower4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbcpower4 STATIC
        src/usbcpower4.c
        src/usbcpower4_app.c
        include/usbcpower4.h
        include/usbcpower4_app.h
)
add_library(Click.USBCPower4  ALIAS lib_usbcpower4)



target_include_directories(lib_usbcpower4 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbcpower4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbcpower4 PUBLIC MikroSDK.Driver)

