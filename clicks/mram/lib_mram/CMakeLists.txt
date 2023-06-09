cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_mram LANGUAGES MikroC)
else()
    project(lib_mram LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_mram STATIC
        src/mram.c
        include/mram.h
)
add_library(Click.MRAM  ALIAS lib_mram)



target_include_directories(lib_mram PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_mram PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_mram PUBLIC MikroSDK.Driver)
