cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_smartcard2 LANGUAGES MikroC)
else()
    project(lib_smartcard2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_smartcard2 STATIC
        src/smartcard2.c
        include/smartcard2.h
)
add_library(Click.SmartCard2  ALIAS lib_smartcard2)



target_include_directories(lib_smartcard2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_smartcard2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_smartcard2 PUBLIC MikroSDK.Driver)
