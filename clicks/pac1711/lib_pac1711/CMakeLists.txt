cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pac1711 LANGUAGES MikroC)
else()
    project(lib_pac1711 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pac1711 STATIC
        src/pac1711.c
        include/pac1711.h
)
add_library(Click.PAC1711  ALIAS lib_pac1711)



target_include_directories(lib_pac1711 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pac1711 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pac1711 PUBLIC MikroSDK.Driver)

