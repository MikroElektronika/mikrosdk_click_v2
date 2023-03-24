cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient15 LANGUAGES MikroC)
else()
    project(lib_ambient15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient15 STATIC
        src/ambient15.c
        include/ambient15.h
)
add_library(Click.Ambient15  ALIAS lib_ambient15)



target_include_directories(lib_ambient15 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient15 PUBLIC MikroSDK.Driver)
