cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nfc2 LANGUAGES MikroC)
else()
    project(lib_nfc2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nfc2 STATIC
        src/nfc2.c
        include/nfc2.h
)
add_library(Click.NFC2  ALIAS lib_nfc2)



target_include_directories(lib_nfc2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nfc2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nfc2 PUBLIC MikroSDK.Driver)
