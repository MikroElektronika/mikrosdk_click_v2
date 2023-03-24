cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_dtmfdecoder LANGUAGES MikroC)
else()
    project(lib_dtmfdecoder LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_dtmfdecoder STATIC
        src/dtmfdecoder.c
        include/dtmfdecoder.h
)
add_library(Click.DTMFDecoder  ALIAS lib_dtmfdecoder)



target_include_directories(lib_dtmfdecoder PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_dtmfdecoder PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_dtmfdecoder PUBLIC MikroSDK.Driver)
