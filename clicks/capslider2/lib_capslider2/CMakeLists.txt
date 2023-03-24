cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_capslider2 LANGUAGES MikroC)
else()
    project(lib_capslider2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_capslider2 STATIC
        src/capslider2.c
        include/capslider2.h
)
add_library(Click.CapSlider2  ALIAS lib_capslider2)



target_include_directories(lib_capslider2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_capslider2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_capslider2 PUBLIC MikroSDK.Driver)
