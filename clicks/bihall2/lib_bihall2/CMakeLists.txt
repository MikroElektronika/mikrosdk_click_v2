cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_bihall2 LANGUAGES MikroC)
else()
    project(lib_bihall2 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_bihall2 STATIC
        src/bihall2.c
        include/bihall2.h
)
add_library(Click.BIHall2  ALIAS lib_bihall2)



target_include_directories(lib_bihall2 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_bihall2 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_bihall2 PUBLIC MikroSDK.Driver)

