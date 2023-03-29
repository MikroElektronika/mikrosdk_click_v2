cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proxfusion3 LANGUAGES MikroC)
else()
    project(lib_proxfusion3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proxfusion3 STATIC
        src/proxfusion3.c
        include/proxfusion3.h
)
add_library(Click.ProxFusion3  ALIAS lib_proxfusion3)



target_include_directories(lib_proxfusion3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proxfusion3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proxfusion3 PUBLIC MikroSDK.Driver)
