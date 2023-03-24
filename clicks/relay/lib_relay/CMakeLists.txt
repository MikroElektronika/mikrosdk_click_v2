cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_relay LANGUAGES MikroC)
else()
    project(lib_relay LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_relay STATIC
        src/relay.c
        include/relay.h
)
add_library(Click.Relay  ALIAS lib_relay)



target_include_directories(lib_relay PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_relay PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_relay PUBLIC MikroSDK.Driver)
