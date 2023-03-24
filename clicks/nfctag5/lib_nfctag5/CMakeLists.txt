cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nfctag5 LANGUAGES MikroC)
else()
    project(lib_nfctag5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nfctag5 STATIC
        src/nfctag5.c
        include/nfctag5.h
)
add_library(Click.NFCTag5  ALIAS lib_nfctag5)



target_include_directories(lib_nfctag5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nfctag5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nfctag5 PUBLIC MikroSDK.Driver)
