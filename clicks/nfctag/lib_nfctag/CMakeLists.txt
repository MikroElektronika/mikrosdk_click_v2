cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nfctag LANGUAGES MikroC)
else()
    project(lib_nfctag LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nfctag STATIC
        src/nfctag.c
        include/nfctag.h
)
add_library(Click.NFCTag  ALIAS lib_nfctag)



target_include_directories(lib_nfctag PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nfctag PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nfctag PUBLIC MikroSDK.Driver)

