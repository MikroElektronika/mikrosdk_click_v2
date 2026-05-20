cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rak11720sma LANGUAGES MikroC)
else()
    project(lib_rak11720sma LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rak11720sma STATIC
        src/rak11720sma.c
        include/rak11720sma.h
)
add_library(Click.RAK11720SMA SMA  ALIAS lib_rak11720sma)



target_include_directories(lib_rak11720sma PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rak11720sma PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rak11720sma PUBLIC MikroSDK.Driver)

