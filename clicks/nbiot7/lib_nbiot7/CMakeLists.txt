cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nbiot7 LANGUAGES MikroC)
else()
    project(lib_nbiot7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nbiot7 STATIC
        src/nbiot7.c
        include/nbiot7.h
)
add_library(Click.NBIoT7  ALIAS lib_nbiot7)



target_include_directories(lib_nbiot7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nbiot7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nbiot7 PUBLIC MikroSDK.Driver)
find_package(MikroSDK.Conversions REQUIRED)
target_link_libraries(lib_nbiot7 PUBLIC MikroSDK.Conversions)

