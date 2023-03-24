cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck23 LANGUAGES MikroC)
else()
    project(lib_buck23 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck23 STATIC
        src/buck23.c
        include/buck23.h
)
add_library(Click.Buck23  ALIAS lib_buck23)



target_include_directories(lib_buck23 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck23 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck23 PUBLIC MikroSDK.Driver)

