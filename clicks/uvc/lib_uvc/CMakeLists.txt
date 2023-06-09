cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_uvc LANGUAGES MikroC)
else()
    project(lib_uvc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_uvc STATIC
        src/uvc.c
        include/uvc.h
)
add_library(Click.Uvc  ALIAS lib_uvc)



target_include_directories(lib_uvc PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_uvc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_uvc PUBLIC MikroSDK.Driver)
