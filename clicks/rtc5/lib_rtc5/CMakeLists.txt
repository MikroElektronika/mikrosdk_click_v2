cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtc5 LANGUAGES MikroC)
else()
    project(lib_rtc5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtc5 STATIC
        src/rtc5.c
        include/rtc5.h
)
add_library(Click.Rtc5  ALIAS lib_rtc5)



target_include_directories(lib_rtc5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtc5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtc5 PUBLIC MikroSDK.Driver)
