cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient11 LANGUAGES MikroC)
else()
    project(lib_ambient11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient11 STATIC
        src/ambient11.c
        include/ambient11.h
)
add_library(Click.Ambient11  ALIAS lib_ambient11)



target_include_directories(lib_ambient11 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient11 PUBLIC MikroSDK.Driver)
