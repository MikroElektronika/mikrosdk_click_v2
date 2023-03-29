cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c2x2key LANGUAGES MikroC)
else()
    project(lib_c2x2key LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c2x2key STATIC
        src/c2x2key.c
        include/c2x2key.h
)
add_library(Click.2x2key  ALIAS lib_c2x2key)



target_include_directories(lib_c2x2key PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c2x2key PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c2x2key PUBLIC MikroSDK.Driver)
