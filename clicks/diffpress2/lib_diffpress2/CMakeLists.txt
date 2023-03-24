cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_diffpress2 LANGUAGES MikroC)
else()
    project(lib_diffpress2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_diffpress2 STATIC
        src/diffpress2.c
        include/diffpress2.h
)
add_library(Click.DiffPress2  ALIAS lib_diffpress2)



target_include_directories(lib_diffpress2 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_diffpress2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_diffpress2 PUBLIC MikroSDK.Driver)
