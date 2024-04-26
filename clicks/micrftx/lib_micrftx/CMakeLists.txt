cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_micrftx LANGUAGES MikroC)
else()
    project(lib_micrftx LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_micrftx STATIC
        src/micrftx.c
        include/micrftx.h
)
add_library(Click.MICRFTX  ALIAS lib_micrftx)



target_include_directories(lib_micrftx PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_micrftx PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_micrftx PUBLIC MikroSDK.Driver)

