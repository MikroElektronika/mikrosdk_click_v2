cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_zigbee LANGUAGES MikroC)
else()
    project(lib_zigbee LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_zigbee STATIC
        src/zigbee.c
        include/zigbee.h
)
add_library(Click.ZigBee  ALIAS lib_zigbee)



target_include_directories(lib_zigbee PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_zigbee PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_zigbee PUBLIC MikroSDK.Driver)
