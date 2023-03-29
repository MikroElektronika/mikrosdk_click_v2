cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wifi9 LANGUAGES MikroC)
else()
    project(lib_wifi9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wifi9 STATIC
        src/wifi9.c
        include/wifi9.h
)
add_library(Click.Wifi9  ALIAS lib_wifi9)



target_include_directories(lib_wifi9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wifi9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wifi9 PUBLIC MikroSDK.Driver)
