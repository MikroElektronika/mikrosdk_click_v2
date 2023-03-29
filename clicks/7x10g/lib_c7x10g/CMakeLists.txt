cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_c7x10g LANGUAGES MikroC)
else()
    project(lib_c7x10g LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_c7x10g STATIC
        src/c7x10g.c
        include/c7x10g.h    include/c7x10g_font.h
)
add_library(Click.7x10G  ALIAS lib_c7x10g)



target_include_directories(lib_c7x10g PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_c7x10g PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_c7x10g PUBLIC MikroSDK.Driver)
