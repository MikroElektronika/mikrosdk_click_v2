cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtc17 LANGUAGES MikroC)
else()
    project(lib_rtc17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtc17 STATIC
        src/rtc17.c
        include/rtc17.h
)
add_library(Click.RTC17  ALIAS lib_rtc17)



target_include_directories(lib_rtc17 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtc17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtc17 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_rtc17 PUBLIC MikroSDK.Conversions)
