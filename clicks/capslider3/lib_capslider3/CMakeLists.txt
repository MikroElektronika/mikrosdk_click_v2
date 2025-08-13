cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_capslider3 LANGUAGES MikroC)
else()
    project(lib_capslider3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_capslider3 STATIC
        src/capslider3.c
        include/capslider3.h
)
add_library(Click.CapSlider3  ALIAS lib_capslider3)



target_include_directories(lib_capslider3 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_capslider3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_capslider3 PUBLIC MikroSDK.Driver)

