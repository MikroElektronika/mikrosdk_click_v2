cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rtc9 LANGUAGES MikroC)
else()
    project(lib_rtc9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rtc9 STATIC
        src/rtc9.c
        include/rtc9.h
)
add_library(Click.Rtc9  ALIAS lib_rtc9)



target_include_directories(lib_rtc9 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rtc9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rtc9 PUBLIC MikroSDK.Driver)
