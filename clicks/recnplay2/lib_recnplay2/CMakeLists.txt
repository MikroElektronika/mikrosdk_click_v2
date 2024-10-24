cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_recnplay2 LANGUAGES MikroC)
else()
    project(lib_recnplay2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_recnplay2 STATIC
        src/recnplay2.c
        include/recnplay2.h
)
add_library(Click.RecNPlay2  ALIAS lib_recnplay2)



target_include_directories(lib_recnplay2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_recnplay2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_recnplay2 PUBLIC MikroSDK.Driver)

