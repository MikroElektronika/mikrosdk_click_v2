cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nfc7i2c LANGUAGES MikroC)
else()
    project(lib_nfc7i2c LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nfc7i2c STATIC
        src/nfc7i2c.c
        include/nfc7i2c.h
)
add_library(Click.NFC7I2C  ALIAS lib_nfc7i2c)



target_include_directories(lib_nfc7i2c PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nfc7i2c PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nfc7i2c PUBLIC MikroSDK.Driver)

