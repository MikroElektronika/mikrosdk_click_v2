cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_captouch LANGUAGES MikroC)
else()
    project(lib_captouch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_captouch STATIC
        src/captouch.c
        include/captouch.h
)
add_library(Click.CapTouch  ALIAS lib_captouch)



target_include_directories(lib_captouch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_captouch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_captouch PUBLIC MikroSDK.Driver)
