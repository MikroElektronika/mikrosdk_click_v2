cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtc LANGUAGES MikroC)
else()
    project(lib_rtc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtc STATIC
        src/rtc.c
        include/rtc.h
)
add_library(Click.Rtc  ALIAS lib_rtc)



target_include_directories(lib_rtc PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtc PUBLIC MikroSDK.Driver)
