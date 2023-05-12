cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ata663211 LANGUAGES MikroC)
else()
    project(lib_ata663211 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ata663211 STATIC
        src/ata663211.c
        include/ata663211.h
)
add_library(Click.Ata663211  ALIAS lib_ata663211)



target_include_directories(lib_ata663211 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ata663211 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ata663211 PUBLIC MikroSDK.Driver)
