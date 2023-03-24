cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rfid LANGUAGES MikroC)
else()
    project(lib_rfid LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rfid STATIC
        src/rfid.c
        include/rfid.h
)
add_library(Click.RFID  ALIAS lib_rfid)



target_include_directories(lib_rfid PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rfid PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rfid PUBLIC MikroSDK.Driver)
