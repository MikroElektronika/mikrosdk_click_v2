cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_trf LANGUAGES MikroC)
else()
    project(lib_trf LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_trf STATIC
        src/trf.c
        include/trf.h
)
add_library(Click.Trf  ALIAS lib_trf)



target_include_directories(lib_trf PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_trf PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_trf PUBLIC MikroSDK.Driver)
