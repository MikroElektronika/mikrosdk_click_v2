cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wifiesp LANGUAGES MikroC)
else()
    project(lib_wifiesp LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wifiesp STATIC
        src/wifiesp.c
        include/wifiesp.h
)
add_library(Click.WifiEsp  ALIAS lib_wifiesp)



target_include_directories(lib_wifiesp PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wifiesp PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wifiesp PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Log REQUIRED)
target_link_libraries(lib_wifiesp PUBLIC MikroSDK.Log)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_wifiesp PUBLIC MikroSDK.GenericPointer)
