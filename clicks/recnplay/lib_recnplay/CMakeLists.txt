cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_recnplay LANGUAGES MikroC)
else()
    project(lib_recnplay LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_recnplay STATIC
        src/recnplay.c
        include/recnplay.h
)
add_library(Click.RecNPlay  ALIAS lib_recnplay)



target_include_directories(lib_recnplay PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_recnplay PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_recnplay PUBLIC MikroSDK.Driver)
