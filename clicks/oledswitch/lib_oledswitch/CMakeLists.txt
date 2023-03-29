cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_oledswitch LANGUAGES MikroC)
else()
    project(lib_oledswitch LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_oledswitch STATIC
        src/oledswitch.c
        include/oledswitch.h
)
add_library(Click.OledSwitch  ALIAS lib_oledswitch)



target_include_directories(lib_oledswitch PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_oledswitch PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_oledswitch PUBLIC MikroSDK.Driver)
