cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient16 LANGUAGES MikroC)
else()
    project(lib_ambient16 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient16 STATIC
        src/ambient16.c
        include/ambient16.h
)
add_library(Click.Ambient16  ALIAS lib_ambient16)



target_include_directories(lib_ambient16 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient16 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient16 PUBLIC MikroSDK.Driver)
