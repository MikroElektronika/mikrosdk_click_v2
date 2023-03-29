cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ata6571 LANGUAGES MikroC)
else()
    project(lib_ata6571 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ata6571 STATIC
        src/ata6571.c
        include/ata6571.h
)
add_library(Click.ATA6571  ALIAS lib_ata6571)



target_include_directories(lib_ata6571 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ata6571 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ata6571 PUBLIC MikroSDK.Driver)
