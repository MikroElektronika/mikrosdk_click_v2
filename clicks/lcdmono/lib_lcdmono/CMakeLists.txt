cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lcdmono LANGUAGES MikroC)
else()
    project(lib_lcdmono LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lcdmono STATIC
        src/lcdmono.c
        include/lcdmono.h
        include/lcdmono_font.h
        include/lcdmono_image.h
)
add_library(Click.LcdMono  ALIAS lib_lcdmono)



target_include_directories(lib_lcdmono PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lcdmono PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lcdmono PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_lcdmono PUBLIC MikroSDK.GenericPointer)
