cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_pulse LANGUAGES MikroC)
else()
    project(lib_pulse LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_pulse STATIC
        src/pulse.c
        include/pulse.h
)
add_library(Click.PULSE  ALIAS lib_pulse)



target_include_directories(lib_pulse PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_pulse PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_pulse PUBLIC MikroSDK.Driver)

