cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_smartnfc LANGUAGES MikroC)
else()
    project(lib_smartnfc LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_smartnfc STATIC
        src/smartnfc.c
        include/smartnfc.h
)
add_library(Click.SmartNFC  ALIAS lib_smartnfc)



target_include_directories(lib_smartnfc PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_smartnfc PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_smartnfc PUBLIC MikroSDK.Driver)

