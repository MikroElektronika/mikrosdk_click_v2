cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_signalrelay LANGUAGES MikroC)
else()
    project(lib_signalrelay LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_signalrelay STATIC
        src/signalrelay.c
        include/signalrelay.h
)
add_library(Click.SignalRealy  ALIAS lib_signalrelay)



target_include_directories(lib_signalrelay PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_signalrelay PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_signalrelay PUBLIC MikroSDK.Driver)
