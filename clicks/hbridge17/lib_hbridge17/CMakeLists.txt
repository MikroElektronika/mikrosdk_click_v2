cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_hbridge17 LANGUAGES MikroC)
else()
    project(lib_hbridge17 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_hbridge17 STATIC
        src/hbridge17.c
        include/hbridge17.h
)
add_library(Click.HBridge17  ALIAS lib_hbridge17)



target_include_directories(lib_hbridge17 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_hbridge17 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_hbridge17 PUBLIC MikroSDK.Driver)

