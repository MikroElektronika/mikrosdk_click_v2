cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtc10 LANGUAGES MikroC)
else()
    project(lib_rtc10 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtc10 STATIC
        src/rtc10.c
        include/rtc10.h
)
add_library(Click.Rtc10  ALIAS lib_rtc10)



target_include_directories(lib_rtc10 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtc10 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtc10 PUBLIC MikroSDK.Driver)
