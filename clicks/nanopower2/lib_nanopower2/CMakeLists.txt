cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nanopower2 LANGUAGES MikroC)
else()
    project(lib_nanopower2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nanopower2 STATIC
        src/nanopower2.c
        include/nanopower2.h
)
add_library(Click.NanoPower2  ALIAS lib_nanopower2)



target_include_directories(lib_nanopower2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nanopower2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nanopower2 PUBLIC MikroSDK.Driver)
