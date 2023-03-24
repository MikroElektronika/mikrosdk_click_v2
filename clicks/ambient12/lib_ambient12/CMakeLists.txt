cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient12 LANGUAGES MikroC)
else()
    project(lib_ambient12 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient12 STATIC
        src/ambient12.c
        include/ambient12.h
)
add_library(Click.Ambient12  ALIAS lib_ambient12)



target_include_directories(lib_ambient12 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient12 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient12 PUBLIC MikroSDK.Driver)
