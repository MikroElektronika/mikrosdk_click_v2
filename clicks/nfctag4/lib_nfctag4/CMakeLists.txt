cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nfctag4 LANGUAGES MikroC)
else()
    project(lib_nfctag4 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nfctag4 STATIC
        src/nfctag4.c
        include/nfctag4.h
)
add_library(Click.NfcTag4  ALIAS lib_nfctag4)



target_include_directories(lib_nfctag4 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nfctag4 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nfctag4 PUBLIC MikroSDK.Driver)
