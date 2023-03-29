cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_efuse5 LANGUAGES MikroC)
else()
    project(lib_efuse5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_efuse5 STATIC
        src/efuse5.c
        include/efuse5.h
)
add_library(Click.eFuse5  ALIAS lib_efuse5)



target_include_directories(lib_efuse5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_efuse5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_efuse5 PUBLIC MikroSDK.Driver)

