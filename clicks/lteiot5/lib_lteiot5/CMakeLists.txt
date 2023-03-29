cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_lteiot5 LANGUAGES MikroC)
else()
    project(lib_lteiot5 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_lteiot5 STATIC
        src/lteiot5.c
        include/lteiot5.h
)
add_library(Click.LTEIoT5  ALIAS lib_lteiot5)



target_include_directories(lib_lteiot5 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_lteiot5 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_lteiot5 PUBLIC MikroSDK.Driver)
