cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nfcextend LANGUAGES MikroC)
else()
    project(lib_nfcextend LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nfcextend STATIC
        src/nfcextend.c
        include/nfcextend.h
)
add_library(Click.NfcExtend  ALIAS lib_nfcextend)



target_include_directories(lib_nfcextend PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nfcextend PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nfcextend PUBLIC MikroSDK.Driver)
