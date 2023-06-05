cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lpwifi LANGUAGES MikroC)
else()
    project(lib_lpwifi LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lpwifi STATIC
        src/lpwifi.c
        include/lpwifi.h
)
add_library(Click.LPWiFi  ALIAS lib_lpwifi)



target_include_directories(lib_lpwifi PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lpwifi PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lpwifi PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_lpwifi PUBLIC MikroSDK.Conversions)
