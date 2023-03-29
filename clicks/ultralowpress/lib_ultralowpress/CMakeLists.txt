cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ultralowpress LANGUAGES MikroC)
else()
    project(lib_ultralowpress LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ultralowpress STATIC
        src/ultralowpress.c
        include/ultralowpress.h
)
add_library(Click.UltraLowPress  ALIAS lib_ultralowpress)



target_include_directories(lib_ultralowpress PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ultralowpress PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ultralowpress PUBLIC MikroSDK.Driver)
