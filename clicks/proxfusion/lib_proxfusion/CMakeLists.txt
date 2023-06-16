cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_proxfusion LANGUAGES MikroC)
else()
    project(lib_proxfusion LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_proxfusion STATIC
        src/proxfusion.c
        include/proxfusion.h
)
add_library(Click.ProxFusion  ALIAS lib_proxfusion)



target_include_directories(lib_proxfusion PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_proxfusion PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_proxfusion PUBLIC MikroSDK.Driver)
