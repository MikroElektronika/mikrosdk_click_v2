cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_neomesh915mhz LANGUAGES MikroC)
else()
    project(lib_neomesh915mhz LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_neomesh915mhz STATIC
        src/neomesh915mhz.c
        include/neomesh915mhz.h
)
add_library(Click.NeoMesh915MHz  ALIAS lib_neomesh915mhz)



target_include_directories(lib_neomesh915mhz PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_neomesh915mhz PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_neomesh915mhz PUBLIC MikroSDK.Driver)

