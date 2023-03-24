cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bihall LANGUAGES MikroC)
else()
    project(lib_bihall LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bihall STATIC
        src/bihall.c
        include/bihall.h
)
add_library(Click.BiHall  ALIAS lib_bihall)



target_include_directories(lib_bihall PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bihall PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bihall PUBLIC MikroSDK.Driver)
