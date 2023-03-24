cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient3 LANGUAGES MikroC)
else()
    project(lib_ambient3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient3 STATIC
        src/ambient3.c
        include/ambient3.h
)
add_library(Click.Ambient3  ALIAS lib_ambient3)



target_include_directories(lib_ambient3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient3 PUBLIC MikroSDK.Driver)
