cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_cordeliai LANGUAGES MikroC)
else()
    project(lib_cordeliai LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_cordeliai STATIC
        src/cordeliai.c
        include/cordeliai.h
)
add_library(Click.CordeliaI  ALIAS lib_cordeliai)



target_include_directories(lib_cordeliai PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_cordeliai PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_cordeliai PUBLIC MikroSDK.Driver)

