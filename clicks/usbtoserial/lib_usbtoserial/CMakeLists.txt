cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbtoserial LANGUAGES MikroC)
else()
    project(lib_usbtoserial LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbtoserial STATIC
        src/usbtoserial.c
        include/usbtoserial.h
)
add_library(Click.USBtoSerial  ALIAS lib_usbtoserial)



target_include_directories(lib_usbtoserial PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbtoserial PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbtoserial PUBLIC MikroSDK.Driver)

