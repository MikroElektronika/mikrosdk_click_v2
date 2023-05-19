cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ata663254 LANGUAGES MikroC)
else()
    project(lib_ata663254 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ata663254 STATIC
        src/ata663254.c
        include/ata663254.h
)
add_library(Click.Ata663254  ALIAS lib_ata663254)



target_include_directories(lib_ata663254 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ata663254 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ata663254 PUBLIC MikroSDK.Driver)
