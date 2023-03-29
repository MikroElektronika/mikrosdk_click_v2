cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nbiot2 LANGUAGES MikroC)
else()
    project(lib_nbiot2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nbiot2 STATIC
        src/nbiot2.c
        include/nbiot2.h
)
add_library(Click.NBIoT2  ALIAS lib_nbiot2)



target_include_directories(lib_nbiot2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nbiot2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nbiot2 PUBLIC MikroSDK.Driver)

