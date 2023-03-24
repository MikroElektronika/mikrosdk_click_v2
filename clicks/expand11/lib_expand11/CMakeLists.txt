cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_expand11 LANGUAGES MikroC)
else()
    project(lib_expand11 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_expand11 STATIC
        src/expand11.c
        include/expand11.h
)
add_library(Click.Expand11  ALIAS lib_expand11)



target_include_directories(lib_expand11 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_expand11 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_expand11 PUBLIC MikroSDK.Driver)

