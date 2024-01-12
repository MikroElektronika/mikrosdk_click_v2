cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_neomesh868mhz LANGUAGES MikroC)
else()
    project(lib_neomesh868mhz LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_neomesh868mhz STATIC
        src/neomesh868mhz.c
        include/neomesh868mhz.h
)
add_library(Click.NeoMesh868MHz  ALIAS lib_neomesh868mhz)



target_include_directories(lib_neomesh868mhz PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_neomesh868mhz PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_neomesh868mhz PUBLIC MikroSDK.Driver)

