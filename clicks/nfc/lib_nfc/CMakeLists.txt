cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nfc LANGUAGES MikroC)
else()
    project(lib_nfc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nfc STATIC
        src/nfc.c
        include/nfc.h
)
add_library(Click.NFC  ALIAS lib_nfc)



target_include_directories(lib_nfc PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nfc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nfc PUBLIC MikroSDK.Driver)

