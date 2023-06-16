cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtc3 LANGUAGES MikroC)
else()
    project(lib_rtc3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtc3 STATIC
        src/rtc3.c
        include/rtc3.h
)
add_library(Click.Rtc3  ALIAS lib_rtc3)



target_include_directories(lib_rtc3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtc3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtc3 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_rtc3 PUBLIC MikroSDK.Conversions)
