cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_watchdog LANGUAGES MikroC)
else()
    project(lib_watchdog LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_watchdog STATIC
        src/watchdog.c
        include/watchdog.h
)
add_library(Click.Watchdog  ALIAS lib_watchdog)



target_include_directories(lib_watchdog PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_watchdog PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_watchdog PUBLIC MikroSDK.Driver)
