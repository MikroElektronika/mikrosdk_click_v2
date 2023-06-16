cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_canfd4 LANGUAGES MikroC)
else()
    project(lib_canfd4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_canfd4 STATIC
        src/canfd4.c
        include/canfd4.h
)
add_library(Click.CanFd4  ALIAS lib_canfd4)



target_include_directories(lib_canfd4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_canfd4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_canfd4 PUBLIC MikroSDK.Driver)
