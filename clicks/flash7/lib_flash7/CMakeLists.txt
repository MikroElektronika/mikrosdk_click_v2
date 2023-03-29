cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_flash7 LANGUAGES MikroC)
else()
    project(lib_flash7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_flash7 STATIC
        src/flash7.c
        include/flash7.h
)
add_library(Click.Flash7  ALIAS lib_flash7)



target_include_directories(lib_flash7 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_flash7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_flash7 PUBLIC MikroSDK.Driver)
