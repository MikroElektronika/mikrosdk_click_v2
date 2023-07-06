cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_canfd6 LANGUAGES MikroC)
else()
    project(lib_canfd6 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_canfd6 STATIC
        src/canfd6.c
        include/canfd6.h
)
add_library(Click.CANFD6  ALIAS lib_canfd6)



target_include_directories(lib_canfd6 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_canfd6 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_canfd6 PUBLIC MikroSDK.Driver)
