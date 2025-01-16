cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ninab222 LANGUAGES MikroC)
else()
    project(lib_ninab222 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ninab222 STATIC
        src/ninab222.c
        include/ninab222.h
)
add_library(Click.NINAB222  ALIAS lib_ninab222)



target_include_directories(lib_ninab222 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ninab222 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ninab222 PUBLIC MikroSDK.Driver)

