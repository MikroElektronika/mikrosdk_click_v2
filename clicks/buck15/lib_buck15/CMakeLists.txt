cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_buck15 LANGUAGES MikroC)
else()
    project(lib_buck15 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_buck15 STATIC
        src/buck15.c
        include/buck15.h
)
add_library(Click.Buck15  ALIAS lib_buck15)



target_include_directories(lib_buck15 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_buck15 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_buck15 PUBLIC MikroSDK.Driver)

