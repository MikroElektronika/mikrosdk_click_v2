cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bldcfoc2 LANGUAGES MikroC)
else()
    project(lib_bldcfoc2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bldcfoc2 STATIC
        src/bldcfoc2.c
        include/bldcfoc2.h
)
add_library(Click.BLDCFOC2  ALIAS lib_bldcfoc2)



target_include_directories(lib_bldcfoc2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bldcfoc2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bldcfoc2 PUBLIC MikroSDK.Driver)

