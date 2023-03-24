cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_nvsram3 LANGUAGES MikroC)
else()
    project(lib_nvsram3 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_nvsram3 STATIC
        src/nvsram3.c
        include/nvsram3.h
)
add_library(Click.nvSRAM3  ALIAS lib_nvsram3)



target_include_directories(lib_nvsram3 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_nvsram3 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_nvsram3 PUBLIC MikroSDK.Driver)
