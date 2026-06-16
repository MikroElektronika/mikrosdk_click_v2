cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tempiso2 LANGUAGES MikroC)
else()
    project(lib_tempiso2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tempiso2 STATIC
        src/tempiso2.c
        include/tempiso2.h
)
add_library(Click.TempISO2  ALIAS lib_tempiso2)



target_include_directories(lib_tempiso2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tempiso2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tempiso2 PUBLIC MikroSDK.Driver)

