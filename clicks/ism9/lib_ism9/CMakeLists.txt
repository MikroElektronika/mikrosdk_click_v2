cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ism9 LANGUAGES MikroC)
else()
    project(lib_ism9 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ism9 STATIC
        src/ism9.c
        include/ism9.h
)
add_library(Click.ISM9  ALIAS lib_ism9)



target_include_directories(lib_ism9 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ism9 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ism9 PUBLIC MikroSDK.Driver)

