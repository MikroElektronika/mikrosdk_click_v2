cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ambient25 LANGUAGES MikroC)
else()
    project(lib_ambient25 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ambient25 STATIC
        src/ambient25.c
        include/ambient25.h
)
add_library(Click.Ambient25  ALIAS lib_ambient25)



target_include_directories(lib_ambient25 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ambient25 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ambient25 PUBLIC MikroSDK.Driver)

