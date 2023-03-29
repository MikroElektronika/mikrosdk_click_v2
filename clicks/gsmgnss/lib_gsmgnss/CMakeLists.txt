cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_gsmgnss LANGUAGES MikroC)
else()
    project(lib_gsmgnss LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_gsmgnss STATIC
        src/gsmgnss.c
        include/gsmgnss.h
)
add_library(Click.GsmGnss  ALIAS lib_gsmgnss)



target_include_directories(lib_gsmgnss PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_gsmgnss PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_gsmgnss PUBLIC MikroSDK.Driver)
find_package(MikroSDK.GenericPointer REQUIRED)
target_link_libraries(lib_gsmgnss PUBLIC MikroSDK.GenericPointer)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_gsmgnss PUBLIC MikroSDK.Conversions)
