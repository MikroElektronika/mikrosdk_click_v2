cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_efuse3 LANGUAGES MikroC)
else()
    project(lib_efuse3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_efuse3 STATIC
        src/efuse3.c
        include/efuse3.h
)
add_library(Click.eFuse3  ALIAS lib_efuse3)



target_include_directories(lib_efuse3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_efuse3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_efuse3 PUBLIC MikroSDK.Driver)
