cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_relay2 LANGUAGES MikroC)
else()
    project(lib_relay2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_relay2 STATIC
        src/relay2.c
        include/relay2.h
)
add_library(Click.Relay2  ALIAS lib_relay2)



target_include_directories(lib_relay2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_relay2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_relay2 PUBLIC MikroSDK.Driver)
