cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_wifi11 LANGUAGES MikroC)
else()
    project(lib_wifi11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_wifi11 STATIC
        src/wifi11.c
        include/wifi11.h
)
add_library(Click.Wifi11  ALIAS lib_wifi11)



target_include_directories(lib_wifi11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_wifi11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_wifi11 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_wifi11 PUBLIC MikroSDK.Conversions)
