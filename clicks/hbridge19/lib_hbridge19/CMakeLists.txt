cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridge19 LANGUAGES MikroC)
else()
    project(lib_hbridge19 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridge19 STATIC
        src/hbridge19.c
        include/hbridge19.h
)
add_library(Click.HBridge19  ALIAS lib_hbridge19)



target_include_directories(lib_hbridge19 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridge19 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridge19 PUBLIC MikroSDK.Driver)

