cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rfid2 LANGUAGES MikroC)
else()
    project(lib_rfid2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rfid2 STATIC
        src/rfid2.c
        include/rfid2.h
)
add_library(Click.RFID2  ALIAS lib_rfid2)



target_include_directories(lib_rfid2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rfid2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rfid2 PUBLIC MikroSDK.Driver)
