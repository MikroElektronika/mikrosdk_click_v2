cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand7 LANGUAGES MikroC)
else()
    project(lib_expand7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand7 STATIC
        src/expand7.c
        include/expand7.h
)
add_library(Click.Expand7  ALIAS lib_expand7)



target_include_directories(lib_expand7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand7 PUBLIC MikroSDK.Driver)
