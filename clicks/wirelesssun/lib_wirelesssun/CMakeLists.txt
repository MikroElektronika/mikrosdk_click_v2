cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wirelesssun LANGUAGES MikroC)
else()
    project(lib_wirelesssun LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wirelesssun STATIC
        src/wirelesssun.c
        include/wirelesssun.h
)
add_library(Click.WirelessSUN  ALIAS lib_wirelesssun)



target_include_directories(lib_wirelesssun PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wirelesssun PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wirelesssun PUBLIC MikroSDK.Driver)
