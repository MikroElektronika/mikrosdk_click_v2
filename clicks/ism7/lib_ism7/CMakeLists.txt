cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_ism7 LANGUAGES MikroC)
else()
    project(lib_ism7 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_ism7 STATIC
        src/ism7.c
        include/ism7.h
)
add_library(Click.ISM7  ALIAS lib_ism7)



target_include_directories(lib_ism7 PUBLIC 
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_ism7 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_ism7 PUBLIC MikroSDK.Driver)

