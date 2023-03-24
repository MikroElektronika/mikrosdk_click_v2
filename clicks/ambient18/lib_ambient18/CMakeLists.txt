cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient18 LANGUAGES MikroC)
else()
    project(lib_ambient18 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient18 STATIC
        src/ambient18.c
        include/ambient18.h
)
add_library(Click.Ambient18  ALIAS lib_ambient18)



target_include_directories(lib_ambient18 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient18 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient18 PUBLIC MikroSDK.Driver)
