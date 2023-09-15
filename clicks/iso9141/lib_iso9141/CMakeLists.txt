cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_iso9141 LANGUAGES MikroC)
else()
    project(lib_iso9141 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_iso9141 STATIC
        src/iso9141.c
        include/iso9141.h
)
add_library(Click.ISO9141  ALIAS lib_iso9141)



target_include_directories(lib_iso9141 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_iso9141 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_iso9141 PUBLIC MikroSDK.Driver)
