cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nanopower LANGUAGES MikroC)
else()
    project(lib_nanopower LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nanopower STATIC
        src/nanopower.c
        include/nanopower.h
)
add_library(Click.NanoPower  ALIAS lib_nanopower)



target_include_directories(lib_nanopower PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nanopower PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nanopower PUBLIC MikroSDK.Driver)
