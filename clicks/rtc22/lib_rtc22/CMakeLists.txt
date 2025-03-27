cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtc22 LANGUAGES MikroC)
else()
    project(lib_rtc22 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtc22 STATIC
        src/rtc22.c
        include/rtc22.h
)
add_library(Click.RTC22  ALIAS lib_rtc22)



target_include_directories(lib_rtc22 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtc22 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtc22 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_rtc22 PUBLIC MikroSDK.Conversions)

