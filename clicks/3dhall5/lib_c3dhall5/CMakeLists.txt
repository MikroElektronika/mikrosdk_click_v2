cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c3dhall5 LANGUAGES MikroC)
else()
    project(lib_c3dhall5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c3dhall5 STATIC
        src/c3dhall5.c
        include/c3dhall5.h
)
add_library(Click.3dHall5  ALIAS lib_c3dhall5)



target_include_directories(lib_c3dhall5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c3dhall5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c3dhall5 PUBLIC MikroSDK.Driver)
