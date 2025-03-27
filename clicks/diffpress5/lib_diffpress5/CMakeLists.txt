cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_diffpress5 LANGUAGES MikroC)
else()
    project(lib_diffpress5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_diffpress5 STATIC
        src/diffpress5.c
        include/diffpress5.h
)
add_library(Click.DiffPress5  ALIAS lib_diffpress5)



target_include_directories(lib_diffpress5 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_diffpress5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_diffpress5 PUBLIC MikroSDK.Driver)

