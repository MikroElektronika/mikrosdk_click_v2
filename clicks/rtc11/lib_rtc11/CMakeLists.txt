cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtc11 LANGUAGES MikroC)
else()
    project(lib_rtc11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtc11 STATIC
        src/rtc11.c
        include/rtc11.h
)
add_library(Click.RTC11  ALIAS lib_rtc11)



target_include_directories(lib_rtc11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtc11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtc11 PUBLIC MikroSDK.Driver)
