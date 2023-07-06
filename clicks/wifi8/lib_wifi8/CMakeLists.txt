cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wifi8 LANGUAGES MikroC)
else()
    project(lib_wifi8 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wifi8 STATIC
        src/wifi8.c
        include/wifi8.h
        include/wifi8_types.h
)
add_library(Click.WiFi8  ALIAS lib_wifi8)



target_include_directories(lib_wifi8 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wifi8 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wifi8 PUBLIC MikroSDK.Driver)
