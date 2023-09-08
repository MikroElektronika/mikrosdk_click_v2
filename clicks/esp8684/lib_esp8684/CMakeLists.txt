cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_esp8684 LANGUAGES MikroC)
else()
    project(lib_esp8684 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_esp8684 STATIC
        src/esp8684.c
        include/esp8684.h
)
add_library(Click.ESP8684  ALIAS lib_esp8684)



target_include_directories(lib_esp8684 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_esp8684 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_esp8684 PUBLIC MikroSDK.Driver)

