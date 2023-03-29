cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient7 LANGUAGES MikroC)
else()
    project(lib_ambient7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient7 STATIC
        src/ambient7.c
        include/ambient7.h
)
add_library(Click.Ambient7  ALIAS lib_ambient7)



target_include_directories(lib_ambient7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient7 PUBLIC MikroSDK.Driver)
