cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_captouch2 LANGUAGES MikroC)
else()
    project(lib_captouch2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_captouch2 STATIC
        src/captouch2.c
        include/captouch2.h
)
add_library(Click.CapTouch2  ALIAS lib_captouch2)



target_include_directories(lib_captouch2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_captouch2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_captouch2 PUBLIC MikroSDK.Driver)
