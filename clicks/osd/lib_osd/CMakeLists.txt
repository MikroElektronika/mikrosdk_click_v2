cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_osd LANGUAGES MikroC)
else()
    project(lib_osd LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_osd STATIC
        src/osd.c
        include/osd.h    include/resources.h
)
add_library(Click.OSD  ALIAS lib_osd)



target_include_directories(lib_osd PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_osd PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_osd PUBLIC MikroSDK.Driver)
