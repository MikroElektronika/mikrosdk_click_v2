cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_powermux LANGUAGES MikroC)
else()
    project(lib_powermux LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_powermux STATIC
        src/powermux.c
        include/powermux.h
)
add_library(Click.PowerMUX  ALIAS lib_powermux)



target_include_directories(lib_powermux PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_powermux PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_powermux PUBLIC MikroSDK.Driver)
