cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_battmon2 LANGUAGES MikroC)
else()
    project(lib_battmon2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_battmon2 STATIC
        src/battmon2.c
        include/battmon2.h
)
add_library(Click.BATTMON2  ALIAS lib_battmon2)



target_include_directories(lib_battmon2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_battmon2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_battmon2 PUBLIC MikroSDK.Driver)
