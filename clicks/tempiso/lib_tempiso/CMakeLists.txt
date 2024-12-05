cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_tempiso LANGUAGES MikroC)
else()
    project(lib_tempiso LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_tempiso STATIC
        src/tempiso.c
        include/tempiso.h
)
add_library(Click.TempISO  ALIAS lib_tempiso)



target_include_directories(lib_tempiso PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_tempiso PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_tempiso PUBLIC MikroSDK.Driver)

