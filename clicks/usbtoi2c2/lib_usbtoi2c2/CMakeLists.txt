cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_usbtoi2c2 LANGUAGES MikroC)
else()
    project(lib_usbtoi2c2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_usbtoi2c2 STATIC
        src/usbtoi2c2.c
        include/usbtoi2c2.h
)
add_library(Click.USBtoI2C2  ALIAS lib_usbtoi2c2)



target_include_directories(lib_usbtoi2c2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_usbtoi2c2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_usbtoi2c2 PUBLIC MikroSDK.Driver)
