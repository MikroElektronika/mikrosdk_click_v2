cmake_minimum_required(VERSION 3.21)
if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(lib_rs2323 LANGUAGES MikroC)
else()
    project(lib_rs2323 LANGUAGES C ASM)
endif()

if (NOT PROJECT_TYPE)
    set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)
endif()

add_library(lib_rs2323 STATIC
        src/rs2323.c
        include/rs2323.h
)
add_library(Click.RS2323  ALIAS lib_rs2323)



target_include_directories(lib_rs2323 PUBLIC
        include
)

find_package(MikroC.Core REQUIRED)
target_link_libraries(lib_rs2323 PUBLIC MikroC.Core)
find_package(MikroSDK.Driver REQUIRED)
target_link_libraries(lib_rs2323 PUBLIC MikroSDK.Driver)
